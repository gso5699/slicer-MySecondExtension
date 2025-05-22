#include "qSlicerMyCppLoadableModuleWidget.h"
#include "ui_qSlicerMyCppLoadableModuleWidget.h"
#include "qSlicerApplication.h"
#include "qSlicerLayoutManager.h"
#include <qMRMLSliceWidget.h>
#include <qMRMLSliceView.h>

#include <QDebug>
#include <QFileDialog>


#include "vtkSlicerMyCppLoadableLogic.h"

#include <vtkPointData.h>
#include <vtkMRMLScalarVolumeNode.h>
#include <vtkRenderWindow.h>
#include <vtkMRMLScene.h>

#include <vtkMRMLSliceNode.h>
#include <vtkMRMLSliceLogic.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkAbstractTransform.h>
#include <vtkMRMLScalarVolumeNode.h>


// Private class that holds UI pointers
class qSlicerMyCppLoadableModuleWidgetPrivate : public Ui_qSlicerMyCppLoadableModuleWidget
{
public:
  qSlicerMyCppLoadableModuleWidgetPrivate() = default;
};

// Constructor
qSlicerMyCppLoadableModuleWidget::qSlicerMyCppLoadableModuleWidget(QWidget* parent)
  : Superclass(parent)
  , d_ptr(new qSlicerMyCppLoadableModuleWidgetPrivate)
{
}

// Destructor
qSlicerMyCppLoadableModuleWidget::~qSlicerMyCppLoadableModuleWidget() = default;

// Setup UI and connect signals
void qSlicerMyCppLoadableModuleWidget::setup()
{
  Q_D(qSlicerMyCppLoadableModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

   // Setup volume selector properties if needed (optional if done in UI)
  d->VolumeSelector->setNodeTypes(QStringList() << "vtkMRMLScalarVolumeNode");
  d->VolumeSelector->setMRMLScene(this->mrmlScene());

  // Connect the combo box signal to your slot
  connect(d->VolumeSelector, SIGNAL(currentNodeChanged(vtkMRMLNode*)),
          this, SLOT(onVolumeNodeSelected(vtkMRMLNode*)));

  // Connect test button clicked signal to your slot
  connect(d->testButton, &QPushButton::clicked,
          this, &qSlicerMyCppLoadableModuleWidget::onRunTestButtonClicked);
  
  // Connect draw button
  connect(d->drawButton, &QPushButton::clicked, this, &qSlicerMyCppLoadableModuleWidget::onDrawButtonClicked);

}

void qSlicerMyCppLoadableModuleWidget::setMRMLScene(vtkMRMLScene* scene)
{
  this->Superclass::setMRMLScene(scene);
  Q_D(qSlicerMyCppLoadableModuleWidget);
  if (d->VolumeSelector)
  {
    d->VolumeSelector->setMRMLScene(scene);
  }
}

// Slot for volume node selection change
void qSlicerMyCppLoadableModuleWidget::onVolumeNodeSelected(vtkMRMLNode* node)
{

  if (node)
  {
    qDebug() << "Selected volume node:" << node->GetName();
   
  }
  else
  {
    qDebug() << "No volume node selected";
  }
}

// Slot for test button clicked
void qSlicerMyCppLoadableModuleWidget::onRunTestButtonClicked()
{
  vtkSlicerMyCppLoadableLogic* myLogic =
    vtkSlicerMyCppLoadableLogic::SafeDownCast(this->logic());

  if (!myLogic)
  {
    qWarning() << "Logic pointer is null.";
    return;
  }

  myLogic->RunMyCppLogic();
}


void qSlicerMyCppLoadableModuleWidget::onDrawButtonClicked()
{
  // Check if the MRML scene is available
  if (!this->mrmlScene())
  {
    qWarning() << "MRML scene is not set.";
    return;
  }

  // Create and initialize paintImage if needed
  if (!this->paintImage)
  {
    this->paintImage = vtkSmartPointer<vtkImageData>::New();
    this->paintImage->SetDimensions(256, 256, 1);
    this->paintImage->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
    unsigned char* ptr = static_cast<unsigned char*>(this->paintImage->GetScalarPointer());
    std::fill(ptr, ptr + 256*256, 0);  // Initialize black
  }

  // Create volume node if not created yet
  if (!this->volumeNode)
  {
    this->volumeNode = vtkSmartPointer<vtkMRMLScalarVolumeNode>::New();
    this->volumeNode->SetName("PaintVolume");
    this->volumeNode->SetAndObserveImageData(this->paintImage);
    this->volumeNode->SetSpacing(1.0, 1.0, 1.0);
    this->volumeNode->SetOrigin(0.0, 0.0, 0.0);

    // Add node to MRML scene
    this->mrmlScene()->AddNode(this->volumeNode);
  }

  // Setup the interactor and callback for painting (as you have)
  auto sliceView = qSlicerApplication::application()->layoutManager()->sliceWidget("Red")->sliceView();
  vtkRenderWindowInteractor* interactor = sliceView->renderWindow()->GetInteractor();

  this->mouseCallback = vtkSmartPointer<vtkCallbackCommand>::New();
  this->mouseCallback->SetClientData(this);
  this->mouseCallback->SetCallback([](vtkObject* caller, unsigned long eventId, void* clientData, void* callData) {
    auto self = static_cast<qSlicerMyCppLoadableModuleWidget*>(clientData);
    auto interactor = static_cast<vtkRenderWindowInteractor*>(caller);
    if (eventId == vtkCommand::LeftButtonPressEvent)
    {
      int* pos = interactor->GetEventPosition();
      self->PaintAtPosition(pos[0], pos[1]);
    }
  });

  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, this->mouseCallback);
}


void qSlicerMyCppLoadableModuleWidget::PaintAtPosition(int x, int y)
{
  if (!this->paintImage)
  {
    qWarning() << "paintImage is not initialized.";
    return;
  }
  if (!this->volumeNode)
  {
    qWarning() << "volumeNode is not set.";
    return;
  }

  // Get slice widget and logic
  // Get slice widget and logic
  qMRMLSliceWidget* sliceWidget = qSlicerApplication::application()->layoutManager()->sliceWidget("Red");
  vtkMRMLSliceLogic* sliceLogic = sliceWidget->sliceLogic();
  vtkMRMLSliceNode* sliceNode = sliceLogic->GetSliceNode();

  // Get the XY to RAS matrix
  vtkMatrix4x4* xyToRAS = sliceNode->GetXYToRAS();

  // Convert display (x, y) to RAS coordinates
  double ras[4] = {0, 0, 0, 1};
  double xy[4] = { static_cast<double>(x), static_cast<double>(y), 0.0, 1.0 };
  xyToRAS->MultiplyPoint(xy, ras);

  // Convert RAS to IJK using volume matrix
  // vtkSmartPointer<vtkMatrix4x4> rasToIJK = vtkSmartPointer<vtkMatrix4x4>::New();
  // this->volumeNode->GetRASToIJKMatrix(rasToIJK);

  // double ijkDouble[4] = {0, 0, 0, 1};
  // rasToIJK->MultiplyPoint(ras, ijkDouble);
  double volumeOrigin[3];
  this->volumeNode->GetOrigin(volumeOrigin);

  double adjustedRAS[4] = {
    ras[0] - volumeOrigin[0],
    ras[1] - volumeOrigin[1],
    ras[2] - volumeOrigin[2],
    1.0
  };

  // Convert adjusted RAS to IJK using volume matrix
  vtkSmartPointer<vtkMatrix4x4> rasToIJK = vtkSmartPointer<vtkMatrix4x4>::New();
  this->volumeNode->GetRASToIJKMatrix(rasToIJK);

  double ijkDouble[4] = {0, 0, 0, 1};
  rasToIJK->MultiplyPoint(adjustedRAS, ijkDouble);

  // Round to nearest voxel indices
  int ijk[3] = {
    static_cast<int>(std::round(ijkDouble[0])),
    static_cast<int>(std::round(ijkDouble[1])),
    static_cast<int>(std::round(ijkDouble[2]))
  };

  qDebug() << "Mouse clicked at:" << x << y
          << "| IJK:" << ijk[0] << ijk[1] << ijk[2];

  int* dims = this->paintImage->GetDimensions();

  // Check IJK voxel bounds (not RAS!)
  if (ijk[0] < 0 || ijk[0] >= dims[0] ||
      ijk[1] < 0 || ijk[1] >= dims[1] ||
      ijk[2] < 0 || ijk[2] >= dims[2])
  {
    qWarning() << "Paint position out of bounds:" << ijk[0] << ijk[1] << ijk[2];
    return;
  }

  // Write to image
  unsigned char* pixel = static_cast<unsigned char*>(this->paintImage->GetScalarPointer(ijk[0], ijk[1], ijk[2]));
  if (pixel)
  {
    *pixel = 255; // Set to white
    this->paintImage->Modified(); // Notify pipeline
    qDebug() << "Painted at:" << ijk[0] << ijk[1] << ijk[2];
  }

}

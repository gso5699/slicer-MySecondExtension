#include "qSlicerMyCppLoadableModuleWidget.h"
#include "ui_qSlicerMyCppLoadableModuleWidget.h"
#include "qSlicerApplication.h"
#include "qSlicerLayoutManager.h"
#include <qMRMLSliceWidget.h>
#include <qMRMLSliceView.h>




#include "vtkSlicerMyCppLoadableLogic.h"
#include <QDebug>
#include <QFileDialog>
#include <vtkPointData.h>
#include <vtkMRMLScalarVolumeNode.h>
#include <vtkRenderWindow.h>
#include <vtkMRMLScene.h>


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

// void qSlicerMyCppLoadableModuleWidget::onDrawButtonClicked()
// {
//   vtkSlicerMyCppLoadableLogic* myLogic =
//     vtkSlicerMyCppLoadableLogic::SafeDownCast(this->logic());
  
//   myLogic->RunPaintLogic();  
// }

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
      qDebug() << "Mouse clicked at: " << pos[0] << pos[1];
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

  // Get image dimensions
  int* dims = this->paintImage->GetDimensions();
  qDebug() << "Image dimensions:" << dims[0] << dims[1] << dims[2];

  // Check if x, y are inside the image bounds
  if (x < 0 || x >= dims[0] || y < 0 || y >= dims[1])
  {
    qWarning() << "Paint position out of bounds:" << x << y;
    return;
  }

  // Set pixel at (x, y) to 255 (white) in the first scalar component
  unsigned char* pixel = static_cast<unsigned char*>(this->paintImage->GetScalarPointer(x, y, 0));
  if (pixel)
  {
    *pixel = 255;
    // Notify that the image data has changed
    this->paintImage->Modified();

    // Optionally, request a scene update so viewers refresh
    // this->GetMRMLScene()->Modified();
  }
  else
  {
    qWarning() << "Failed to get pixel pointer at" << x << y;
  }
}


#include "qSlicerMyCppLoadableModuleWidget.h"
#include "ui_qSlicerMyCppLoadableModuleWidget.h"

#include "vtkSlicerMyCppLoadableLogic.h"
#include <QDebug>
#include <QFileDialog>


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

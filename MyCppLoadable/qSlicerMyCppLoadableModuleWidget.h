#ifndef __qSlicerMyCppLoadableModuleWidget_h
#define __qSlicerMyCppLoadableModuleWidget_h

// Slicer includes
#include "qSlicerAbstractModuleWidget.h"


// MRML includes
#include <vtkMRMLNode.h>
#include <qMRMLNodeComboBox.h>
#include <vtkMRMLScalarVolumeNode.h>


#include "qSlicerMyCppLoadableModuleExport.h"

#include <QPushButton>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCallbackCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMRMLSliceViewInteractorStyle.h>


class qSlicerMyCppLoadableModuleWidgetPrivate;

class Q_SLICER_QTMODULES_MYCPPLOADABLE_EXPORT qSlicerMyCppLoadableModuleWidget
  : public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:
  typedef qSlicerAbstractModuleWidget Superclass;
  explicit qSlicerMyCppLoadableModuleWidget(QWidget* parent = nullptr);
  ~qSlicerMyCppLoadableModuleWidget() override;

public slots:
  void onVolumeNodeSelected(vtkMRMLNode* node);
  void setMRMLScene(vtkMRMLScene* scene) override;
  void onRunTestButtonClicked();
  void PaintAtPosition(int x, int y);

protected:
  void setup() override;
  void onDrawButtonClicked();

protected:
  QScopedPointer<qSlicerMyCppLoadableModuleWidgetPrivate> d_ptr;
  vtkSmartPointer<vtkImageData> paintImage;
  vtkSmartPointer<vtkMRMLScalarVolumeNode> volumeNode;


private:
  Q_DECLARE_PRIVATE(qSlicerMyCppLoadableModuleWidget);
  Q_DISABLE_COPY(qSlicerMyCppLoadableModuleWidget);
  qMRMLNodeComboBox *VolumeSelector;

  QPushButton* drawButton;
  vtkSmartPointer<vtkCallbackCommand> mouseCallback;
  bool paintingActive = false;
};

#endif

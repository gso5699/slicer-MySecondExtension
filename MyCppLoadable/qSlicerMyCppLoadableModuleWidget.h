#ifndef __qSlicerMyCppLoadableModuleWidget_h
#define __qSlicerMyCppLoadableModuleWidget_h

// Slicer includes
#include "qSlicerAbstractModuleWidget.h"


// MRML includes
#include <vtkMRMLNode.h>
#include <qMRMLNodeComboBox.h>

#include "qSlicerMyCppLoadableModuleExport.h"

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

protected:
  void setup() override;

protected:
  QScopedPointer<qSlicerMyCppLoadableModuleWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerMyCppLoadableModuleWidget);
  Q_DISABLE_COPY(qSlicerMyCppLoadableModuleWidget);
  qMRMLNodeComboBox *VolumeSelector;
};

#endif

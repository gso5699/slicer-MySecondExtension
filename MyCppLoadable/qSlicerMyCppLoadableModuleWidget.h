/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerMyCppLoadableModuleWidget_h
#define __qSlicerMyCppLoadableModuleWidget_h

// Slicer includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerMyCppLoadableModuleExport.h"

class qSlicerMyCppLoadableModuleWidgetPrivate;
class vtkMRMLNode;

class Q_SLICER_QTMODULES_MYCPPLOADABLE_EXPORT qSlicerMyCppLoadableModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerMyCppLoadableModuleWidget(QWidget *parent=0);
  virtual ~qSlicerMyCppLoadableModuleWidget();

public slots:


protected:
  QScopedPointer<qSlicerMyCppLoadableModuleWidgetPrivate> d_ptr;

  void setup() override;

private:
  Q_DECLARE_PRIVATE(qSlicerMyCppLoadableModuleWidget);
  Q_DISABLE_COPY(qSlicerMyCppLoadableModuleWidget);
};

#endif

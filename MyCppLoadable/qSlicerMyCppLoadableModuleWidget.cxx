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

// Qt includes
#include <QDebug>
#include <QPushButton>

// Slicer includes
#include "qSlicerMyCppLoadableModuleWidget.h"
#include "ui_qSlicerMyCppLoadableModuleWidget.h"
#include "vtkSlicerMyCppLoadableLogic.h"

// -----------------------------------------------------------------------------
class qSlicerMyCppLoadableModuleWidgetPrivate: public Ui_qSlicerMyCppLoadableModuleWidget
{
public:
  qSlicerMyCppLoadableModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerMyCppLoadableModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableModuleWidgetPrivate::qSlicerMyCppLoadableModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerMyCppLoadableModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableModuleWidget::qSlicerMyCppLoadableModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerMyCppLoadableModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableModuleWidget::~qSlicerMyCppLoadableModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerMyCppLoadableModuleWidget::setup()
{
  Q_D(qSlicerMyCppLoadableModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  // add test button
  QPushButton* testButton = new QPushButton("Run Logic Test");
  this->layout()->addWidget(testButton);

  connect(testButton, &QPushButton::clicked,
          this, &qSlicerMyCppLoadableModuleWidget::onRunTestButtonClicked);

  
}


void qSlicerMyCppLoadableModuleWidget::onRunTestButtonClicked()
{
  auto* myLogic = vtkSlicerMyCppLoadableLogic::SafeDownCast(this->logic());
  if (!myLogic)
  {
    qWarning() << "Logic pointer is null.";
    return;
  }
  myLogic->RunMyCppLogic();
}
/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerMyCppLoadableFooBarWidget.h"
#include "ui_qSlicerMyCppLoadableFooBarWidget.h"

//-----------------------------------------------------------------------------
class qSlicerMyCppLoadableFooBarWidgetPrivate
  : public Ui_qSlicerMyCppLoadableFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerMyCppLoadableFooBarWidget);
protected:
  qSlicerMyCppLoadableFooBarWidget* const q_ptr;

public:
  qSlicerMyCppLoadableFooBarWidgetPrivate(
    qSlicerMyCppLoadableFooBarWidget& object);
  virtual void setupUi(qSlicerMyCppLoadableFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerMyCppLoadableFooBarWidgetPrivate
::qSlicerMyCppLoadableFooBarWidgetPrivate(
  qSlicerMyCppLoadableFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerMyCppLoadableFooBarWidgetPrivate
::setupUi(qSlicerMyCppLoadableFooBarWidget* widget)
{
  this->Ui_qSlicerMyCppLoadableFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerMyCppLoadableFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableFooBarWidget
::qSlicerMyCppLoadableFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerMyCppLoadableFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerMyCppLoadableFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableFooBarWidget
::~qSlicerMyCppLoadableFooBarWidget()
{
}

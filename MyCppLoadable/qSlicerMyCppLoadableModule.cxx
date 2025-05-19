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

// MyCppLoadable Logic includes
#include <vtkSlicerMyCppLoadableLogic.h>

// MyCppLoadable includes
#include "qSlicerMyCppLoadableModule.h"
#include "qSlicerMyCppLoadableModuleWidget.h"

//-----------------------------------------------------------------------------
class qSlicerMyCppLoadableModulePrivate
{
public:
  qSlicerMyCppLoadableModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerMyCppLoadableModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableModulePrivate::qSlicerMyCppLoadableModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerMyCppLoadableModule methods

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableModule::qSlicerMyCppLoadableModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerMyCppLoadableModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerMyCppLoadableModule::~qSlicerMyCppLoadableModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerMyCppLoadableModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerMyCppLoadableModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerMyCppLoadableModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerMyCppLoadableModule::icon() const
{
  return QIcon(":/Icons/MyCppLoadable.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerMyCppLoadableModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerMyCppLoadableModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerMyCppLoadableModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerMyCppLoadableModule
::createWidgetRepresentation()
{
  return new qSlicerMyCppLoadableModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerMyCppLoadableModule::createLogic()
{
  return vtkSlicerMyCppLoadableLogic::New();
}

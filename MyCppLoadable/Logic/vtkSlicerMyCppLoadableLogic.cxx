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
#include "vtkSlicerMyCppLoadableLogic.h"


// MRML includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkImageData.h>


// STD includes
#include <cassert>
#include <vtkMRMLScalarVolumeNode.h>
#include <vtkMRMLVolumeArchetypeStorageNode.h>
#include <vtkNew.h>
#include <QDebug>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerMyCppLoadableLogic);

//----------------------------------------------------------------------------
vtkSlicerMyCppLoadableLogic::vtkSlicerMyCppLoadableLogic()
{
}

//----------------------------------------------------------------------------
vtkSlicerMyCppLoadableLogic::~vtkSlicerMyCppLoadableLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerMyCppLoadableLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//---------------------------------------------------------------------------
void vtkSlicerMyCppLoadableLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerMyCppLoadableLogic::RegisterNodes()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerMyCppLoadableLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerMyCppLoadableLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerMyCppLoadableLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}


// My test logic
void vtkSlicerMyCppLoadableLogic::RunMyCppLogic()
{
  std::cout << "[RunMyCppLogic] Called from widget button!" << std::endl;
}

void vtkSlicerMyCppLoadableLogic::RunPaintLogic()
{
  std::cout << "[RunPaintLogic] Called from widget button!" << std::endl;
  vtkSmartPointer<vtkMRMLScalarVolumeNode> volumeNode = vtkSmartPointer<vtkMRMLScalarVolumeNode>::New();

  volumeNode->SetName("PaintVolume");
  vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
  imageData->SetDimensions(256, 256, 1);
  imageData->AllocateScalars(VTK_UNSIGNED_CHAR, 1);  // 1 channel, 8-bit unsigned
  volumeNode->SetAndObserveImageData(imageData);
  volumeNode->SetSpacing(1.0, 1.0, 1.0);
  volumeNode->SetOrigin(0.0, 0.0, 0.0);
  this->GetMRMLScene()->AddNode(volumeNode);
}
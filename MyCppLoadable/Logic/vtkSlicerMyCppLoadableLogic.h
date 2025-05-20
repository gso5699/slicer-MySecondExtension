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

// .NAME vtkSlicerMyCppLoadableLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerMyCppLoadableLogic_h
#define __vtkSlicerMyCppLoadableLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"

// MRML includes

// STD includes
#include <cstdlib>

#include "vtkSlicerMyCppLoadableModuleLogicExport.h"
#include <QString>



class VTK_SLICER_MYCPPLOADABLE_MODULE_LOGIC_EXPORT vtkSlicerMyCppLoadableLogic :
  public vtkSlicerModuleLogic
{
public:

  static vtkSlicerMyCppLoadableLogic *New();
  vtkTypeMacro(vtkSlicerMyCppLoadableLogic, vtkSlicerModuleLogic);

  void PrintSelf(ostream& os, vtkIndent indent) override;
  void RunMyCppLogic();

  bool LoadPNGAsScalarVolumeNode(const QString& filePath, vtkMRMLScene* scene);

protected:
  vtkSlicerMyCppLoadableLogic();
  ~vtkSlicerMyCppLoadableLogic() override;

  void SetMRMLSceneInternal(vtkMRMLScene* newScene) override;
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  void RegisterNodes() override;
  void UpdateFromMRMLScene() override;
  void OnMRMLSceneNodeAdded(vtkMRMLNode* node) override;
  void OnMRMLSceneNodeRemoved(vtkMRMLNode* node) override;

private:

  vtkSlicerMyCppLoadableLogic(const vtkSlicerMyCppLoadableLogic&); // Not implemented
  void operator=(const vtkSlicerMyCppLoadableLogic&); // Not implemented
};

#endif

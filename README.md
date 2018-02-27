# Branch-structured-Face-detector-SDK
## Brief description
This face detector is an efficient detector that can obtain higher performance but use less memory. It was developed on the basis of a manuscript titled "Branch-structured detector for fast and robust face detection using asymmetric LBP features". Recently, We have submitted the manuscript for publication in a peer-reviewed journal. The main contributions of our manuscript are as follows: 
- We designed a branch-structured detector.
- We proposed a pixel-level image feature named Asymmetric LBP feature (ALBP).
- We proposed a method for introducing ALBP features into a branch-structured face detector.
## Performance and Efficiency Evaluation
![Alt text](/Images/ROC.jpg  "Fig 1. Discrete ROC curve for our detector on FDDB Dataset.")

Fig 1. Discrete ROC curve for our detector on FDDB Dataset.

Table 1. Detection speed of our detector

|    CPU      | Image size | Min Face | Step | Scale factor | Needed memory | FPS                       |
|    :---:    | :---:      | :---:    | :---: | :---:       | :---:         | :---:                     |
| G2030@3.0GHz, 2 threads | 640\*480    |  40\*40  | 3    |1.2        |15MB               | 163.3(a.jpg), 88.8(b.jpg) |
| G2030@3.0GHz, 2 threads | 640\*480    | 80\*80   | 3    |1.2        |15MB               | 389.7(a.jpg), 238.6(b.jpg) |

|![Alt text](/Images/a.jpg)|  ![Alt text](/Images/b.jpg)


## Requirement
* Windows (Windows7 has been validated).
* C++ compiler (Visual studio 2013 has been validated).
## How to Create an face detection program with Visual Studio 2013
1. Create a project: FILE -> New -> Project... -> Visual C++ -> Win32 -> Win32 Console Application. 
2. Include necessary header files in .cpp files.

   For instance, we create a project named "test". Then, a .cpp file named "test.cpp" will be created automatically. In the test.cpp file, header files should be included as follows:
   
   <pre><code>#include "opencv2/highgui/highgui.hpp"
   #include "opencv2/imgproc/imgproc.hpp"
   #include "bsFaceDetector.h"</code></pre>
3. Add "<SDK_Folder>\include" to Additional Include Directories: (Project) Properities -> Configuration Properties -> C/C++ -> General -> Additional Include Directories.

   <SDK_Folder> represents the folder which stores SDK files. For instance, the SDK files are stored at d:\BSFD_SDK,  <SDK_Folder> would represent "d:\BSFD_SDK" .
  
4. Add "<SDK_Folder>\lib\x64" (or "<SDK_Folder>\lib\x86") to Additional Library Directories: (Project) Properities -> Configuration Properties -> Linker -> General -> Additional Libray Directories.
5. Add necessary Static Libraries to Additional Dependencies: (Project) Properities -> Configuration Properties -> Linker -> Input -> Additional Dependencies. The necessary Static Libraries are:
   * opencv_highgui2411.lib
   * opencv_core2411.lib
   * bsFaceDetector.lib
   * seeta_facedet_lib.lib
6. Build project.
7. Copy model files to the folder which stores the executable file (.exe) created by visual studio 2013. The model files that should be copied are:
   * cascadeModels.bin
   * seeta_fd_frontal_v1.0.bin
8. Add "<SDK_Folder>\Dll\x64" (or "<SDK_Folder>\Dll\x86") to the PATH environment variable: 
9. Reboot your computer.
10. Run the executable file from Command Prompt.
   

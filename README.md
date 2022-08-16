# Branch-structured-Face-detector-SDK
## Brief description
This is a detector that can make a trade-off between efficiency and performance for face detection. It was developed on the basis of our paper: 
Chen, Jc., Wang, J., Zhao, Lp. et al. Branch-structured detector for fast face detection using asymmetric LBP features. SIViP 14, 1699–1706 (2020). https://doi.org/10.1007/s11760-020-01710-7
The main contributions of our manuscript are as follows: 
- We designed a branch-structured detector.
- We proposed a pixel-level image feature named Asymmetric LBP feature (ALBP).
- We proposed a method for introducing ALBP features into a branch-structured face detector.
## Performance and Efficiency Evaluation
![Alt text](/Images/ROC.jpg  "Fig 1. Discrete ROC curve for our detector on FDDB Dataset.")

Fig 1. Discrete ROC curve for our detector on FDDB Dataset.

Table 1. Detection speed of our detector

|  CPU    | Image Size| Step | Scale factor | Needed memory | Threads| Min Face | FPS      |
| ---   | ---  | --- | --- | --- | ---    | ---- | ---   |
| i7-7700 | 640\*480 | 3  |1.2  |15MB  | 4  |  40\*40  | 316(a.jpg), 197(b.jpg) |
| i7-7700 | 640\*480 | 3  |1.2  |15MB  | 4  | 80\*80   | 784(a.jpg), 572(b.jpg) |
| i7-7700 | 640\*480 | 3  |1.2  |15MB  | 2  |  40\*40  | 301(a.jpg), 186(b.jpg) |
| i7-7700 | 640\*480 | 3  |1.2  |15MB  | 2  | 80\*80   | 767(a.jpg), 554(b.jpg) |
| i7-7700 | 640\*480 | 3  |1.2  |15MB  | 1  |  40\*40  | 261(a.jpg), 167(b.jpg) |
| i7-7700 | 640\*480 | 3  |1.2  |15MB  | 1  | 80\*80   | 741(a.jpg), 529(b.jpg) |

|![Alt text](/Images/a.jpg)|  ![Alt text](/Images/b.jpg)|
|    :---:    | :---:      |
|    a.jpg    | b.jpg      |


## Requirement
* Windows (Windows7 has been validated).
* C++ compiler \[Visual studio 2013 (Community version) has been validated].
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
8. Copy the .dll files that are stored in "<SDK_Folder>\Dll\x64" (or "<SDK_Folder>\Dll\x86") to the folder which stores the executable file (.exe) created by visual studio 2013. 
9. Run the executable file from Command Prompt.
## Contact with us
<pre><code>Email: chenjiechun@neepu.edu.cn
QQ: 418044891</code></pre>

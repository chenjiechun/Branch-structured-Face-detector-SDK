# Branch-structured-Face-detector-SDK
## Brief description
This face detector is an efficient detector that can obtain higher performance but use less memory. It was developed on the basis of a manuscript titled "Branch-structured detector for fast and robust face detection using asymmetric LBP features". Recently, We have submitted the manuscript for publication in a peer-reviewed journal. The main contributions of our manuscript are as follows: 
- We designed a branch-structured detector.
- We proposed a pixel-level image feature named Asymmetric LBP feature (ALBP).
- We proposed a method for introducing ALBP features into a branch-structured face detector.
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
3. Add "<SDK_Folder>\include" to additional include directories: (Project) Properities -> Configuration Properties -> C/C++ -> General -> Additional Include Directories.

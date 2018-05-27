# WatermarkApp
BachelorDegree

I have developed an application using the C++ C# interoperabilty with OpenCv libraries under the title Watermark images for my bachelor 
degree thesis. A digital watermak is a kind of undercover hidden marker in a noise tolerance signal, such as audio, video or image data. 
It is usually used to identify the copyright ownership of such a signal. 
"Watermarking" is the process of hiding digital information in a carrier signal. Digital watermarkers can be used to verify the authenticity 
or integrity of the carrier signal or to show the identity of its owners. It is prominently used for tracking copyright infringement. 
The project is an WPF C# and C++ application. The C++ Engine has two implementations that use OpenCv digital imaging libraries, an implementation
with an invisible digital watermark encryption method using a Least Significant Bit (LSB) algorithm and an implementation with a method of 
encoding a visible watermark by using a mask image. 
For binding the WPF C# application with C++ project i used a new project called EngineWrapper who is an CLI project which contains the methods 
that makes the bridge between C++ and C#. Practicaly the only thing that i had to do now was to add C++ project as a reference to EngineWrapper 
and after that the EngineWrapper project as an refernce to the WPF C# project. In the end at runtime the method that is called is the C++ 
process method. The result is converted into an image wich WPF will display it.

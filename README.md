# number_identification
A number identification app by C++/Python and OpenCV.
## environment
    Xcode 11.4
    clang 11.0.3
    OpenCV 4.1.2
    Python 3.6
    Debian sid riscv64 (LowRISC)
## method
      We thought about the identification of each number, and if we slice them with two threshold horizontally,  
    and one vertically, we will find the difference. We use different numbers to distinct the changes for   
    each numbers at threshold lines. The relationship between them is written in each code.  
      The methods of template matching, deep learning, etc. are not suggested as it's hard to implement in   
    riscv system.
## result
![](https://github.com/Loow-Teech/number_identification/blob/master/results.png)

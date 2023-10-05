# LogBazooka
LogBazooka - For when print statements aren't enough.

## What is it?
Many years ago (around 2000) I was working a lot with Crystal Reports. 
I would extend Crystal Reports with CRUFL libraries, and debugging between what was going on in Crystal reports
and what was going on in the library meant a lot of slow debug statements everywhere. So, I had a VB6 application
called "Coulls Tools" that subclassed a VB window frame, and redirected WM_COPYDATA messages through a routine
to copy out the memory and thus, I could see logically what was happening in real time as the reports ran.

Fast forward to 2023 and I realised that even though many people know what I do, there's nothing public in a repo 
showing people what I am capable of...  Despite spending 90% of my working days in Python on a Mac, I also wanted to show that I
still had some Windows chops, and so here we are.... "Coulls Tools" is now "LogBazooka" and it's written in C++ using Win32.

## Is it complete? 
No.  It's a work in progress.  I've not even written instructions on how to use it.  I do have a roadmap in my head, though.  

## Warning
Use at your own peril. 

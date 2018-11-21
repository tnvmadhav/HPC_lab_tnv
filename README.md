# HPC_lab_tnv



## General syntax for executing code
```
$ c++ <filename>.cpp -fopenmp
$ ./a.out <size_of_input> <no._of_threads>
```


### Pprog2_tnv_2

```
$ c++ pprog2_tnv.cpp -fopenmp
$ ./a.out 1000000 4
```

```
Serial PI : 3.142123 
Actual PI  :3.141593 
Time: 0.148911 
 Parallel PI : 3.141608 
 Actual PI : 3.141593 
Time: 0.030931 
```

------------------------------------------------------------------------------------------------------------------------
### pprog6.c

#### gd APIs involved :
1. gdImageCreateFromPng(file pointer)
2. gdImageSX(img)
3. gdImageSY(img)
4. gdImageGetPixel(img, x, y)
5. gdImageRed(img , color)
6. gdImageGreen(img , color)
7. gdImageBlue(img , color)
8. gdImageColorAllocate(img , red , green , blue)
9. gdImageSetPixel(img , x, y, color)
10. gdImagePng(img , fp)
11. gfImageDestroy(img)

```
$ cc pprog6.c -fopenmp -lgd
$ ./a.out mitta.png output.png 4
File Size: 300x168
Time Taken: 2.870ms

```
Input : mitta.png

![mitta](https://user-images.githubusercontent.com/17908655/45671561-5353bd80-bb43-11e8-93cc-5f6cf1540d23.png)

Output : output.png

![output](https://user-images.githubusercontent.com/17908655/45671562-5353bd80-bb43-11e8-8dea-475528366f45.png)

-----------------------------------------------------------------------------------------------------------------------------


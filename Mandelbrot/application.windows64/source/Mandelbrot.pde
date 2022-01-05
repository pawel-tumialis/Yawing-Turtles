ArrayList <PVector> pts;
float ReMin, ReMax, ImMin, ImMax;
float Xr, Yr, X0, Y0;
int n;

float WIDHEI, MAX_ITER, INF_VAL;

int inputWid, inputHei;
int []mandPixels, inputPixels, mandPixels2;
PImage inputImg, mandelImg, mandelEdgeImg;
PrintWriter output;
color []mandel;

float MIN = MAX_FLOAT, GUESS;
float STEP, OFFS, MAX_X, MAX_Y;

int iter_num , repeat_num , prevIterMin;
long T_START, T_FINISH;
boolean STOP_SEARCH, FINISHED, START_SEARCH, DIVERGE, INIT, SHOW_ANIM, SHOW_IMGS;
  
void setup()
{
  size(800, 400);
  println("PRESS [S] TO SHOW IMAGES");
  println("PRESS [A] TO ANIM SEARCH");
  println("PRESS [SPACE] TO START/PAUSE SEARCH");
  println("PRESS [ENTER] TO FINISH");
  T_START = millis();
  int compSize = 200;
  
  pts = new ArrayList <PVector>();
  
  STOP_SEARCH = true;
  FINISHED = false;
  INIT = true;
  SHOW_ANIM = false;
  SHOW_IMGS = false;
  
  Xr = 0;
  Yr = 0;
  X0 = 0;
  Y0 = 0;
  
  prevIterMin = 0;
  iter_num = 0;
  repeat_num = 0;
  
  STEP = 0.2;
  OFFS = 2.0;
  MAX_X = 2.0 - OFFS;
  MAX_Y = 2.0 - OFFS;
  
  MAX_ITER = 50;
  INF_VAL = 16;
  
  ReMin = -1.00000;
  ReMax = 1.00000;
  ImMin = -1.00000;
  ImMax = 1.00000;
  
  n = 1;
  WIDHEI = 2.0/n;
  
  inputImg = loadImage("przykład_fraktale_1.png"); 
  output = createWriter("przykład_fraktale_1.txt");
  
  inputImg.loadPixels();
  for (int y = 0; y < inputImg.height; y++) 
    for (int x = 0; x < inputImg.width; x++) 
    { 
      int pos = y*inputImg.width + x;
      float sum = 0;
      float r = red(inputImg.pixels[pos]);
      float g = green(inputImg.pixels[pos]);
      float b = blue(inputImg.pixels[pos]);
      int val = int((r + g + b)/3);
      if(val < 140)
        sum = 0;
      else 
        sum = 255; 
         
      inputImg.pixels[pos] = color(sum);  
    }
    
  inputImg.resize(compSize, compSize);
  inputHei = inputImg.height;
  inputWid = inputImg.width;
  
  mandelImg = createImage(inputWid, inputHei, RGB);
  mandelImg.loadPixels();
  
  mandPixels = new int[inputHei*inputWid];
  mandPixels2 = new int[inputHei*inputWid];
  inputPixels = new int[inputHei*inputWid];
  
  for (int y = 0; y < inputImg.height; y++) 
    for (int x = 0; x < inputImg.width; x++) 
    {
      int pos = y*inputImg.width + x;
      inputPixels[pos] = int(red(inputImg.pixels[pos]));
    }
  
  EdgeDetMand();
  //if(black_num/(inputHei*inputWid) < 0.2)
  //    n += 15;
}
 
void draw()
{
    //if(millis() - T_START > 120000)    
    //   FINISHED = true;

    if(!STOP_SEARCH && !FINISHED)
      brute();
    else if(FINISHED)
    {  
      calcMandel2(X0, Y0, ImMax - ImMin);
      updateImg();
      image(inputImg, width/2, 0, width/2, height);
      image(mandelImg, 0, 0, width/2, height);
      T_FINISH = millis();
      println(MIN);
      println("FINISHED");
      noLoop();
      long T = T_FINISH - T_START;
      output.println(nf(ReMin, 0, 5));
      output.println(nf(ReMax, 0, 5));
      output.println(nf(ImMin, 0, 5));
      output.println(nf(ImMax, 0, 5));
      output.println(T);
      output.flush();
      output.close();  
    }
    
    if(SHOW_IMGS)
    {
      image(inputImg, width/2, 0, width/2, height);
      image(mandelImg, 0, 0, width/2, height);
    } else if(STOP_SEARCH)
    {
      image(mandelEdgeImg, 0, 0, width/2, height);
      background(0);
    }
}

void keyPressed()
{
  if (key == ' ')
      STOP_SEARCH = !STOP_SEARCH;
  if (key == ENTER)
      FINISHED = true;
  if (key == 'A' || key == 'a')
      SHOW_ANIM = !SHOW_ANIM;     
  if (key == 'S' || key == 's')
      SHOW_IMGS = !SHOW_IMGS;
}

void brute()
{        
    if (iter_num > pts.size() || INIT || 
    (!DIVERGE && repeat_num > 1000 ) || (DIVERGE && Xr >= MAX_X && Yr >= MAX_Y))
    {
        if(INIT)
         INIT = false;
        
        n++;
        WIDHEI = 2.0/n;
        
        if(repeat_num > 1000)
          DIVERGE = true;

        println(n);
        println("MIN : " + MIN);
        
        if(DIVERGE)
        {
          Xr = pts.get(prevIterMin).x;
          Yr = pts.get(prevIterMin).y;
          
          OFFS = 2*WIDHEI;
          STEP = OFFS/(n*8);
          MAX_X = Xr + OFFS/2;
          MAX_Y = Yr + OFFS/2;
          Xr -= OFFS/2;
          Yr -= OFFS/2;  
        } else
        {
          iter_num = int(STEP + 5*n);
          STEP = 10 - n/5;
        }
    }

    if (repeat_num > 2000)
         FINISHED = true;

    if(!DIVERGE)
    {
      Xr = pts.get(iter_num).x;
      Yr = pts.get(iter_num).y;
    } else if(Xr >= MAX_X)
    {
      Xr = pts.get(prevIterMin).x - OFFS;
      Yr += STEP;
    }
    
    calcMandel2(Xr, Yr, WIDHEI);
    GUESS = comp();
    
    if(SHOW_ANIM)
        updateImg();
    
    if(GUESS < MIN)
    {
      MIN = GUESS;
      updateImg();
      repeat_num = 0;
      prevIterMin = iter_num; 
      ReMin = Xr - WIDHEI/2.0f;
      ReMax = Xr + WIDHEI/2.0f;
      ImMin = Yr - WIDHEI/2.0f;
      ImMax = Yr + WIDHEI/2.0f;
      X0 = Xr;
      Y0 = Yr;
    }   
    
    if(!DIVERGE)
      iter_num += STEP;
    else
      Xr += STEP;
      
    repeat_num++;
}

void calcMandel2(float X, float Y, float WH)
{
  float a, b, iter; 
  
  for (int x = 0; x < inputWid; x++)
    for (int y = 0; y < inputHei; y++)
    {
      a = map(x, 0, inputWid, X - WH/2.0f, X + WH/2.0f);
      b = map(y, 0, inputHei, Y - WH/2.0f, Y + WH/2.0f);
      
      iter = 0;
      
      float cc1 = a;
      float cc2 = b;
      
      while (iter < MAX_ITER)
      {
        float aa = a*a - b*b; // Re {z} z = a + ib
        float bb = 2 * a * b; // Im {z} z^2 = a^2 + 2abi i b^2
        
        a = aa + cc1;
        b = bb + cc2;
        
        if ( abs(a + b) > INF_VAL)
          break; 
        iter++;
      }

      float brg;
      if(iter == MAX_ITER)
        brg = 0.0f; 
      else 
        brg = 255.0f;
      
      int ind = y*inputWid + x;
      mandPixels2[ind] = int(brg);
    }  
}

float comp()
{ 
  float diff = 0;
  
   for (int x = 0; x < inputWid; x++)
     for (int y = 0; y < inputHei; y++)
     {
        int ind = y*inputWid + x;   
        int px1 = inputPixels[ind];
        int px2 = mandPixels2[ind];
        
        diff += abs(px1 - px2);
     }
     
     return diff;
}

void updateImg()
{
  for (int x = 0; x < inputWid; x++)
     for (int y = 0; y < inputHei; y++)
     {
      int i = y*inputWid + x;
      int brg = mandPixels2[i];
      color col = color(brg);
      mandelImg.pixels[i] = col;
      mandelImg.updatePixels();
    }
}

void EdgeDetMand()
{
 int imgSize = 800;
  float []mandPixelEdge = new float[imgSize*imgSize] ;
  mandelEdgeImg = createImage(imgSize, imgSize, RGB);
  mandelEdgeImg.loadPixels();
 
 float a, b, iter;
 
 for (int y = 0; y < imgSize; y++)
    for (int x = 0; x < imgSize; x++)
    {
      a = map(x, 0, imgSize, -1.0f, 1.0f);
      b = map(y, 0, imgSize, -1.0f, 1.0f);
      
      iter = 0;
      
      float cc1 = a;
      float cc2 = b;
      
      while (iter < MAX_ITER)
      {
        float aa = a*a - b*b; // Re {z} z = a + ib
        float bb = 2 * a * b; // Im {z} z^2 = a^2 + 2abi i b^2
        
        a = aa + cc1;
        b = bb + cc2;
        
        if ( abs(a + b) > INF_VAL)
          break; 
        iter++;
      }

      float brg;
      if(iter == MAX_ITER)
        brg = 0.0f; 
      else 
        brg = 255.0f;
      
      mandPixelEdge[y*imgSize + x] = brg;
    }
   
   // SOBEL HORIZONTAL OPERATOR
    float hor_kernel[] =
    {
        -1.0f, 0.0f, 1.0f,
        -2.0f, 0.0f, 2.0f,
        -1.0f, 0.0f, 1.0f,
    };

    // SOBEL VERTICAL OPERATOR
    float ver_kernel[] =
    {
        -1.0f, -2.0f, -1.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 2.0f, 1.0f,
    };
  
  int pts_index = 0;
  
    for(int y = 0; y < imgSize; y++)
      for(int x = 0; x < imgSize; x++)
      {
        float sobelH = 0.0f;
        float sobelW = 0.0f;
  
        for (int n = -1; n < 2; n++)
            for (int m = -1; m < 2; m++)
            {
                int index = (y + n) * imgSize + x + m;
                if (index >= 0 && index < imgSize*imgSize)
                {
                    sobelH += mandPixelEdge[index] * ver_kernel[(m + 1) * 3 + (n + 1)];
                    sobelW += mandPixelEdge[index] * hor_kernel[(m + 1) * 3 + (n + 1)];
                }
            }
              
          float val = sqrt(sobelH * sobelH + sobelW * sobelW)/4;
  
          if (val > 255.0f)
            val = 255.0f;
  
          if (val < 244.0f)
            val = 0.0f;
            
          mandelEdgeImg.pixels[y * imgSize + x] = color(int(val));
          float xx = map(x, 0, imgSize, -1.0f, 1.0f);
          float yy = map(y, 0, imgSize, -1.0f, 1.0f);
          
          if (val > 244.0f)
            pts.add(pts_index, new PVector(xx, yy));
      }   
      println(pts.size());
}

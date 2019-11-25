%clear all, close all, clc

opts=acfTrain();
opts.modelDs=[64 64];
opts.modelDsPad=[64 64];
opts.pPyramid.pChns.pColor.smooth=0;
opts.nWeak=[64 256 1024 2048];
opts.pBoost.pTree.maxDepth=4;
opts.pBoost.discrete=0;
opts.pBoost.pTree.fracFtrs=1/16;
opts.nNeg=25000;
opts.nAccNeg=50000;
opts.pPyramid.pChns.pGradHist.softBin=1;
opts.pJitter=struct('flip',1);
opts.pPyramid.pChns.shrink=1;
opts.name='C:\Users\CAV\Turtle_bot_pro\AcfMyModel';
opts.stride = 6;
opts.cascThr = -8;pLoad={'lbls',{'person'},'ilbls',{'people'},'squarify',{3,.41}};
opts.pLoad = [pLoad 'hRng',[50 inf], 'vRng',[1 1] ];
opts.posWinDir='C:\Users\CAV\Turtle_bot_pro\Images\Turtlebotimg';
opts.negWinDir='C:\Users\CAV\Turtle_bot_pro\Images\False_img_env';
detector = acfTrain( opts );

%Trained on 03-30-2018
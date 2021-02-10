%Make sure run this script in the same file folder with other .csv data
%%This section reads all the file needed in this coursework
white = csvread('WhiteLED.csv');
purple = csvread('PurpleLaser.csv');
green = csvread('GreenLaser.csv');
red = csvread('RedLaser.csv');
Y = [405;
     532;
     650];
b_dye = csvread('BlueDye.csv');
r_dye = csvread('RedDye.csv');
b_dye_blk = csvread('BlankForBlue.csv');
r_dye_blk = csvread('BlankForBlue.csv');

%%This section finds the pixel value of the peak from the laser spectra
[p_val,p_pixel] = max(purple);
[g_val, g_pixel] = max(green);
[r_val, r_pixel] = max(red);

%%This section constructs matrices for the overdetermined linear system
%%and solve for the coefficients m and c
A = [p_pixel 1;
     g_pixel 1;
     r_pixel 1];
x = A\Y;
m = x(1);
c = x(2);

%%This section converts intensity of each pixel to wavelength of each pixel
wavelengths = (1:length(white))*m +c;
%%This section calculates the absorbance 
b_abs = 1-b_dye./b_dye_blk;
r_abs = 1 - r_dye./r_dye_blk;
%%This section removes absorbance below 420nm and above 680nm
idx = find(wavelengths>420 & wavelengths<680);
%Plot the figure to make sure the segmentation has been done correctly

[~,b_abs] = plot_spectra('BlueDye',wavelengths,b_abs,idx);
[truncated_w, r_abs]=plot_spectra('RedDye', wavelengths,r_abs,idx);
%%This section smoothes the data by using moving mean algorithm
smooth_data_b = my_smooth(b_abs,100);
smooth_data_r = my_smooth(r_abs,100);
%%Plot the graph again to make sure the smooth function is working
figure(3)
plot(truncated_w,b_abs)
title('BlueDye smoothed');
xlabel('wavelength (nm)');
ylabel('Abs');
hold on
plot(truncated_w,smooth_data_b)

figure(4)
plot(truncated_w,r_abs)
title('RedDye smoothed');
xlabel('wavelength (nm)');
ylabel('Abs');
hold on
plot(truncated_w,smooth_data_r)
%%This section exports the smoothed data 
writematrix(smooth_data_b,'smooth_data_BlueDye.csv');
writematrix(smooth_data_r,'smooth_data_RedDye.csv');
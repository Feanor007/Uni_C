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
[p_val, p_pixel] = max(purple);
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
smooth_data_w = my_smooth(white,100);
smooth_data_b = my_smooth(b_abs,100);
smooth_data_r = my_smooth(r_abs,100);
%%Plot the graph again to make sure the smooth function is working
figure(3)
plot(truncated_w,b_abs)
title('BlueDye smoothed');
xlabel('wavelength (nm)');
ylabel('Abs');
hold on
plot(truncated_w,smooth_data_b,'LineWidth',2.0)

figure(4)
plot(truncated_w,r_abs)
title('RedDye smoothed');
xlabel('wavelength (nm)');
ylabel('Abs');
hold on
plot(truncated_w,smooth_data_r,'LineWidth',2.0)

figure(5)
plot(wavelengths, white);
title('WhiteLED')
xlabel('wavelength (nm)');
ylabel('Abs');
hold on
plot(wavelengths,smooth_data_w)
%%This section exports the smoothed data 
writematrix(smooth_data_b,'smooth_data_BlueDye.csv');
writematrix(smooth_data_r,'smooth_data_RedDye.csv');

%%Define Functions
function smooth_data = my_smooth(data,win_size)
n = length(data);
smooth_data = zeros(1,n);
for i = 1:n
    if (i <= win_size/2)
        start = 1;
        stop = start + win_size;
    elseif(i >= n - win_size/2)
        start = i - win_size/2;
        stop = n;
    else
        start = i - win_size/2;
        stop = start + win_size;
    end
    %The following three lines of code were used for debugging
    %disp(start)
    %check = stop - start;
    %disp(check);
    smooth_data(i) = sum(data(start:stop))/(stop-start+1);
end
end
function [new_wavelengths,new_abs]=plot_spectra(dye,wavelengths,abs,idx)
figure()
plot(wavelengths,abs)
title(dye);
xlabel('wavelength (nm)');
ylabel('Abs')
hold on
new_wavelengths = wavelengths(idx);
new_abs = abs(idx);
plot(new_wavelengths,new_abs)
end
clear
file = "..\testCickleGalileo.txt";
data =importdata(file);
%1 ������ ;%��� �� ������
MU = 0; SIGMA = data(:,2);
X = -3*SIGMA:0.01:3*SIGMA; %������ ���� n �������� �� ����� �� -3 �� 3
%  Z = normcdf(X,MU,SIGMA);
% figure (1)
%  plot(X,Z)
%  figure (2)
 sigma = SIGMA;
 x = X;
 M0= 0; %�� ������ �����������
 f = (1./(sigma.*sqrt(2*pi))).*exp((-(x-M0).^2)./(2*sigma.^2));
 %%for i = 1:length(f)
  % plot(x(1,:),f)
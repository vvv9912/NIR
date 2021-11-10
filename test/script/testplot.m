clear
file = "..\Galileo_H.txt";
data = importdata(file);
%1 ������ ;%��� �� ������

sigmax = data(:,2);
sigmay = data(:,3);
sigma = sqrt(sigmax.^2+sigmay.^2)
x = -3*sigma:0.01:3*sigma; %������ ���� n �������� �� ����� �� -3 �� 3
M0 = data(:,1);
% M0= 0; %�� ������ �����������
 for i = 1:length(data(:,2))
 x = (-3*sigma+M0(i)):0.01:(3*sigma+M0(i));
 f(i,:) = (1./(sigma(i).*sqrt(2*pi))).*exp((-(x-M0(i)).^2)./(2*sigma(i).^2));
 end
 figure (1)
for i = 1:length(f(:,1))
   x = (-3*sigma+M0(i)):0.01:(3*sigma+M0(i));
   plot(x(1,:),f(i,:))
   hold on;
   grid on;
end
%   f = (1./(sigma.*sqrt(2*pi))).*exp((-(x-0).^2)./(2*sigma.^2));
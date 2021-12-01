clear
fileGa = "..\Galileo_rand.log";
fileGl = "..\Glonass_rand.log";
fileG = "..\GPS_rand.log";
dataGa = importdata(fileGa);
dataGl = importdata(fileGl);
dataG = importdata(fileG);
pars(dataGa,1)
pars(dataGl,2)
pars(dataG,3)
%1 высота ;%ско по высоте
% function p = pars(data, nfigure)
% sigmax = data(:,4);
% sigmay = data(:,5);
% sigma = sqrt(sigmax.^2+sigmay.^2);
% x = -3*sigma:0.01:3*sigma; %должно быть n массивов по длине от -3 до 3
% M0 = data(:,1);
% % M0= 0; %от высоты зависимость
%  for i = 1:length(data(:,2))
%  x = (-3*sigma+M0(i)):0.01:(3*sigma+M0(i));
%  f(i,:) = (1./(sigma(i).*sqrt(2*pi))).*exp((-(x-M0(i)).^2)./(2*sigma(i).^2));
%  end
%  figure (nfigure)
% for i = 1:length(f(:,1))
%    x = (-3*sigma+M0(i)):0.01:(3*sigma+M0(i));
%    plot(x(1,:),f(i,:))
%    hold on;
%    grid on;
% endhistogram(dataG(:,4),500)
% end
function p = pars(data, nfigure)
sigmax = data(:,4);
sigmay = data(:,5);
besk = -1;
novsb = -10;
for (i = 1:length(sigmax))
if (sigmax(i) == (besk))
 sigma(i) = sigmax(i);
elseif ((sigmax(i) == (novsb)))
    sigma(i) = sigmax(i);
else
 sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2);
sigma(i) = 3*sigma(i);
end
end
M0 = data(:,1);
L = data(:,3);
B = data(:,2);
% M0= 0; %от высоты зависимость
 
 figure (nfigure)

%    plot(L,sigma,'o')
%       hold on;
%    grid on;
%     ylabel('3*\sigma');
%    xlabel('L, gr')
%    ylim([novsb 70])
    if (mod(nfigure,1) == 0)
       title('Galileo')
    end
     if (mod(nfigure,2) == 0)
        title('Glonass')
     end
     if (mod(nfigure,3) == 0)
        title('GPS')
    end
%    figure (nfigure+3)
%    plot(B,sigma,'o')
   
%    ylabel('3*\sigma');
%    xlabel('B, gr')
    histogram (sigma);
  %       ylim([0 3500])
      xlim([novsb 20])
%     axis auto
      set(gca, 'XTick',novsb:1:20)
    xlabel('3*\sigma')
    ylabel('кол-во экспериментов');
   hold on;
   grid on;
    if (mod(nfigure,1) == 0)
       title('Galileo')
    end
     if (mod(nfigure,2) == 0)
        title('Glonass')
     end
     if (mod(nfigure,3) == 0)
        title('GPS')
    end

end
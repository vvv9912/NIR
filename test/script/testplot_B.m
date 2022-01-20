clear
close all
fileGa = "..\Galileo_B.txt";
fileGl = "..\Glonass_B.txt";
fileG = "..\GPS_B.txt";
fileB = "..\Beidou_B.txt";
dataGa = importdata(fileGa);
dataGl = importdata(fileGl);
dataG = importdata(fileG);
dataB = importdata(fileB);
pars(dataGa,1)
pars(dataGl,2)
pars(dataG,3)
pars(dataB,4)
%1 высота ;%ско по высоте
% function p = pars(data, nfigure)
% sigmax = data(:,2);
% sigmay = data(:,3);
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
% end
% end
function p = pars(data, nfigure)
sigmax = data(:,1);
sigmay = data(:,2);
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

x = data(:,4);

 
 figure (nfigure)

    if (mod(nfigure,1) == 0)
       title('Galileo')
    end
     if (mod(nfigure,2) == 0)
        title('Glonass')
     end
     if (mod(nfigure,3) == 0)
        title('GPS')
     end
  plot(x,sigma)
    xlabel('B, градусы')
    ylabel('3*\sigma, м');
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
       if (mod(nfigure,4) == 0)
        title('Beidou')
    end

end
% % % % % % % %для прошлой версии
% % % % % % % function p = pars(data, nfigure)
% % % % % % % sigmax = data(:,2);
% % % % % % % sigmay = data(:,3);
% % % % % % % besk = -1;
% % % % % % % novsb = -10;
% % % % % % % for (i = 1:length(sigmax))
% % % % % % % if (sigmax(i) == (besk))
% % % % % % %  sigma(i) = sigmax(i);
% % % % % % % elseif ((sigmax(i) == (novsb)))
% % % % % % %     sigma(i) = sigmax(i);
% % % % % % % else
% % % % % % %  sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2);
% % % % % % % sigma(i) = 3*sigma(i);
% % % % % % % end
% % % % % % % end
% % % % % % % 
% % % % % % % x = data(:,1);
% % % % % % % 
% % % % % % %  
% % % % % % %  figure (nfigure)
% % % % % % % 
% % % % % % %     if (mod(nfigure,1) == 0)
% % % % % % %        title('Galileo')
% % % % % % %     end
% % % % % % %      if (mod(nfigure,2) == 0)
% % % % % % %         title('Glonass')
% % % % % % %      end
% % % % % % %      if (mod(nfigure,3) == 0)
% % % % % % %         title('GPS')
% % % % % % %      end
% % % % % % %   plot(x,sigma)
% % % % % % %     xlabel('B')
% % % % % % %     ylabel('3*\sigma, м');
% % % % % % %    hold on;
% % % % % % %    grid on;
% % % % % % %     if (mod(nfigure,1) == 0)
% % % % % % %        title('Galileo')
% % % % % % %     end
% % % % % % %      if (mod(nfigure,2) == 0)
% % % % % % %         title('Glonass')
% % % % % % %      end
% % % % % % %      if (mod(nfigure,3) == 0)
% % % % % % %         title('GPS')
% % % % % % %      end
% % % % % % %        if (mod(nfigure,4) == 0)
% % % % % % %         title('Beidou')
% % % % % % %     end
% % % % % % % 
% % % % % % % end
%   f = (1./(sigma.*sqrt(2*pi))).*exp((-(x-0).^2)./(2*sigma.^2));
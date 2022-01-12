
fileGa = "..\Galileo_rand.log";
fileGl = "..\Glonass_rand.log";
fileG = "..\GPS_rand.log";
fileBeidou = "..\Beidou_rand.log";
 dataGa = importdata(fileGa);
 dataGl = importdata(fileGl);
 dataG = importdata(fileG);
dataBeidou = importdata(fileBeidou);
%  pars(dataGa,1,20000,-10,20,1)
%   pars(dataGl,2,2000,-10,50,1)
 % pars(dataG,3,2000,-10,20,1)
  pars(dataBeidou,4,2000000,-10,500,10)
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
function p = pars(data, nfigure,shag, min, max, shag2)
sigmax = data(:,9);
sigmay = data(:,10);
sigmaz = data(:,11);
besk = -1;
novsb = -10;
for (i = 1:length(sigmax))
if (sigmax(i) == (besk))
 sigma(i) = sigmax(i);
elseif ((sigmax(i) == (novsb)))
    sigma(i) = sigmax(i);
else
 sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2+sigmaz(i).^2);
sigma(i) = 3*sigma(i);
end
end

M0 = data(:,1);
L = data(:,3);
B = data(:,2);
M0= 0; %от высоты зависимость
 
 figure (nfigure)
%  z = 1;
% for (i = 1: length(sigma)) 
% if (sigma(i)<0)
% a(z)=sigma(i);
% z = z+1;
% end
% end
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
    histogram (sigma,shag);
  %       ylim([0 3500])
      xlim([min max])
       ylim([0 30])
%     axis auto
      set(gca, 'XTick',min:shag2:max)
       %set(gca, 'XTick',0:10:600)
    xlabel('3*\sigma, м')
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
       if (mod(nfigure,4) == 0)
        title('Beidou')
    end

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % function p = pars(data, nfigure)
% % sigmax = data(:,9);
% % sigmay = data(:,10);
% % sigmaz = data(:,11);
% % besk = -1;
% % novsb = -10;
% % for (i = 1:length(sigmax))
% % if (sigmax(i) == (besk))
% %  sigma(i) = sigmax(i);
% % elseif ((sigmax(i) == (novsb)))
% %     sigma(i) = sigmax(i);
% % else
% %  sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2+sigmaz(i).^2);
% % sigma(i) = 3*sigma(i);
% % end
% % end
% % 
% % M0 = data(:,1);
% % L = data(:,3);
% % B = data(:,2);
% % % M0= 0; %от высоты зависимость
% %  
% %  figure (nfigure)
% % %  z = 1;
% % % for (i = 1: length(sigma)) 
% % % if (sigma(i)<0)
% % % a(z)=sigma(i);
% % % z = z+1;
% % % end
% % % end
% % %    plot(L,sigma,'o')
% % %       hold on;
% % %    grid on;
% % %     ylabel('3*\sigma');
% % %    xlabel('L, gr')
% % %    ylim([novsb 70])
% %     if (mod(nfigure,1) == 0)
% %        title('Galileo')
% %     end
% %      if (mod(nfigure,2) == 0)
% %         title('Glonass')
% %      end
% %      if (mod(nfigure,3) == 0)
% %         title('GPS')
% %     end
% % %    figure (nfigure+3)
% % %    plot(B,sigma,'o')
% %    
% % %    ylabel('3*\sigma');
% % %    xlabel('B, gr')
% %     histogram (sigma);
% %   %       ylim([0 3500])
% %       xlim([0 20])
% % %     axis auto
% %       set(gca, 'XTick',novsb:1:20)
% %     xlabel('3*\sigma, м')
% %     ylabel('кол-во экспериментов');
% %    hold on;
% %    grid on;
% %     if (mod(nfigure,1) == 0)
% %        title('Galileo')
% %     end
% %      if (mod(nfigure,2) == 0)
% %         title('Glonass')
% %      end
% %      if (mod(nfigure,3) == 0)
% %         title('GPS')
% %     end
% % 
% % end
% %%%%%%%%%%%%%%%%
% function p = pars(data, nfigure)
% sigmax = data(:,4);
% sigmay = data(:,5);
% besk = -1;
% novsb = -10;
% for (i = 1:length(sigmax))
% if (sigmax(i) == (besk))
%  sigma(i) = sigmax(i);
% elseif ((sigmax(i) == (novsb)))
%     sigma(i) = sigmax(i);
% else
%  sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2);
% sigma(i) = 3*sigma(i);
% end
% end
% M0 = data(:,1);
% L = data(:,3);
% B = data(:,2);
% % M0= 0; %от высоты зависимость
%  
%  figure (nfigure)
% %  z = 1;
% % for (i = 1: length(sigma)) 
% % if (sigma(i)<0)
% % a(z)=sigma(i);
% % z = z+1;
% % end
% % end
% %    plot(L,sigma,'o')
% %       hold on;
% %    grid on;
% %     ylabel('3*\sigma');
% %    xlabel('L, gr')
% %    ylim([novsb 70])
%     if (mod(nfigure,1) == 0)
%        title('Galileo')
%     end
%      if (mod(nfigure,2) == 0)
%         title('Glonass')
%      end
%      if (mod(nfigure,3) == 0)
%         title('GPS')
%     end
% %    figure (nfigure+3)
% %    plot(B,sigma,'o')
%    
% %    ylabel('3*\sigma');
% %    xlabel('B, gr')
%     histogram (sigma);
%   %       ylim([0 3500])
%       xlim([novsb 20])
% %     axis auto
%       set(gca, 'XTick',novsb:1:20)
%     xlabel('3*\sigma, м')
%     ylabel('кол-во экспериментов');
%    hold on;
%    grid on;
%     if (mod(nfigure,1) == 0)
%        title('Galileo')
%     end
%      if (mod(nfigure,2) == 0)
%         title('Glonass')
%      end
%      if (mod(nfigure,3) == 0)
%         title('GPS')
%     end
% 
% end
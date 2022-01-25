close all
clear all

fileGa = "..\Galileo_rand.log";
fileGl = "..\Glonass_rand.log";
fileG = "..\GPS_rand.log";
fileBeidou = "..\Beidou_rand.log";
 dataGa = importdata(fileGa);
 dataGl = importdata(fileGl);
 dataG = importdata(fileG);
dataBeidou = importdata(fileBeidou);
  pars(dataGa,1,2000,0,20,1,2500)
   pars(dataGl,2,2000,0,20,1,350)
 pars(dataG,3,2000,0,20,1,700)
  pars(dataBeidou,4,10000000,-10,500,10,100)
%   pars(dataBeidou,4,50,0,300,10,100)
%1 высота ;%ско по высоте

function p = pars(data, nfigure,shag, min, max, shag2,ymax)
sigmax = data(:,9);
sigmay = data(:,10);
sigmaz = data(:,11);
besk = -10;
novsb = -1;
for (i = 1:length(sigmax))
if (sigmax(i) == (besk))
 sigma(i) = sigmax(i);
elseif ((sigmax(i) == (novsb)))
    sigma(i) = besk;
    sigma(i) = sigmax(i);
else
 sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2);
sigma(i) = 3*sigma(i);
if(sigma(i) >= (300))
    sigma(i)=-100;
end
end
end
%удалим не нужные значения
B = sort(sigma); %расположим по возр
n = 0; % откуда массив больше 0 
for (i = 1:length(B))
    if (B(i) >=0)
      n = i;
      break
    end
end
%
sigma = B(i:length(B));
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

%    figure (nfigure+3)
%    plot(B,sigma,'o')
   
%    ylabel('3*\sigma');
%    xlabel('B, gr')
 if (mod(nfigure,1) == 0)
       name ='GALILEO';
    end
     if (mod(nfigure,2) == 0)
        name ='ГЛОНАСС';
     end
     if (mod(nfigure,3) == 0)
        name ='GPS';
     end
       if (mod(nfigure,4) == 0)
        name ='BEIDOU';
    end
    histogram (sigma,shag);
  %       ylim([0 3500])
      xlim([min max])
      ylim([0 ymax])
%     axis auto
      set(gca, 'XTick',min:shag2:max)
       %set(gca, 'XTick',0:10:600)
    xlabel('3*\sigma, м')
    ylabel('кол-во экспериментов');
   hold on;
   grid on;
   title(name);
%    set(findall(gcf,'type','axes'),'fontsize',5)
%    set(findall(gcf,'type','text'),'fontSize',10) 
%    saveas(gcf,'beidou1.png');
  
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
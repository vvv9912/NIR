cd d:\my\NIR\test\erorr
close all;clc;clear
fileB = "beidou_err.log";
dataB = importdata(fileB);
fileGPS = "gpserr.log";
dataGPS = importdata(fileGPS);
fileGalileo = "fGalileo_err.log";
dataGalileo =  importdata(fileGalileo);
fileGlonass = "GLNSerr.log";
dataGlonass = importdata(fileGlonass);
pars(dataGalileo,1);
pars(dataGlonass,1);
pars(dataGPS,1);
pars(dataB,1);
% function p = pars(data, nfigure)
% nsp = data(:,1);
% SISRE = data(:,2);
% M0 = data(:,3);
% if (mod(nfigure,1) == 0)
%        name = 'GALILEO';
%         %title('Galileo')
%     end
%      if (mod(nfigure,2) == 0)
%            name = '�������';
%       %  title('Glonass')
%      end
%      if (mod(nfigure,3) == 0)
%        name ='GPS';
%         % title('GPS')
%      end
%        if (mod(nfigure,4) == 0)
%             name ='BEIDOU';
%       %  title('Beidou')
%     end
%  figure (nfigure)
%  
%    bar(nsp,SISRE)
%    
%    xlabel('����� ��������')
%    ylabel('{\sigma^2}_{SISRE}, �');
%    hold on;
%    grid on;
%    title(name);
%    ylim([0 30]);
%    set(gca, 'XTick',0:1:max(nsp))
% %    set(gca,'FontSize',9)
%    set(findall(gcf,'type','axes'),'fontsize',5)
%    set(findall(gcf,'type','text'),'fontSize',12) 
%    n = string(nfigure);
%    nn = "_"
%    n2 = ".jpg"
%    SKOO = "_SKO_";
%    saveas(nfigure,name+SKOO+n+n2);
%    
%    figure (nfigure+4)
%    
%    bar(nsp,M0)
%    
%    xlabel('����� ��������')
%    ylabel('{M}_{SISRE}, �');
%    hold on;
%    grid on;
%    set(gca, 'XTick',0:1:max(nsp))
%    n = string(nfigure+4);
% %saveas(h1,'fig2.png')
%    ylim([0 30]);
%    M = "_M_";
%    title(name);
%    set(findall(gcf,'type','axes'),'fontsize',5)
%    set(findall(gcf,'type','text'),'fontSize',12) 
% saveas(nfigure+4,name+M+n+n2);
% end
% % ��� ����������� �� ����� ������� ���� ����
function p = pars(data, nfigure)
nsp = data(:,1);
SISRE = data(:,2);
M0 = data(:,3);
% if (mod(nfigure,1) == 0)
%        name = 'Galileo';
%         %title('Galileo')
%     end
%      if (mod(nfigure,2) == 0)
%            name = 'Glonass';
%       %  title('Glonass')
%      end
%      if (mod(nfigure,3) == 0)
%        name ='GPS';
%         % title('GPS')
%      end
%        if (mod(nfigure,4) == 0)
%             name ='Beidou';
%       %  title('Beidou')
%        end
    name ='���_�������';
 figure (nfigure)
   bar(nsp,SISRE)
   xlabel('����� ��������')
   ylabel('{\sigma^2}_{SISRE}, �');
   hold on;
   grid on;
  % title(name);
   ylim([0 30]);
   set(gca, 'XTick',0:1:max(nsp))
%    set(gca,'FontSize',9)
   set(findall(gcf,'type','axes'),'fontsize',5)
   set(findall(gcf,'type','text'),'fontSize',12) 
   n = string(nfigure);
   nn = "_"
   n2 = ".jpg"
   SKOO = "_SKO_";
   legend('GALILEO','�������','GPS','BEIDOU','Location','northwest' );
   saveas(nfigure,name+SKOO+n+n2);
   
   figure (nfigure+4)
   bar(nsp,M0)
   xlabel('����� ��������')
   ylabel('{M}_{SISRE}, �');
   hold on;
   grid on;
   set(gca, 'XTick',0:1:max(nsp))
   n = string(nfigure+4);
%saveas(h1,'fig2.png')
   ylim([0 30]);
   M = "_M_";
%   title(name);
   set(findall(gcf,'type','axes'),'fontsize',5)
   set(findall(gcf,'type','text'),'fontSize',12) 
    legend('GALILEO','�������','GPS','BEIDOU','Location','northwest' );
saveas(nfigure+4,name+M+n+n2);

end
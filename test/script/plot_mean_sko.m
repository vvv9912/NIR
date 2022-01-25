close all
clearvars  -except  dataB dataG dataGl dataGa

% fileGa = "..\rand_B\Galileo_B_rand.log";
% fileGl = "..\rand_B\Glonass_B_rand.log";
% fileG = "..\rand_B\GPS_B_rand.log";
% fileB = "..\rand_B\Beidou_B_rand.log";
%
fileGa = "..\Galileo_B_rand.log";
fileGl = "..\Glonass_B_rand.log";
fileG = "..\GPS_B_rand.log";
fileB = "..\Beidou_B_rand.log";
dataGa = importdata(fileGa);
dataGl = importdata(fileGl);
dataG = importdata(fileG);
dataB = importdata(fileB);
%1<<H<<"2"<<L<<"3"<<B<<"4"<< sko2[0]<<"5"<<sko2[1]<<"6"<<sko2[2]<<"7"<<sko2[3]
%<<"8"<<sko2[4]<<"9"<< COORDD[0]<<"10"<<COORDD[1]<<"11"<<COORDD[2]<<"12"<<Bg
%<<13<<Lg<<14<<Hg<<"\n";
% n = 1;
% for (b= -90:1:90)
% for (i = 1:1:length(dataGa))
%    if (dataGa(i,3) == b)
%    %9%10%11 coord[0:1]
%    Galileo_coord(i,:) = dataGa(i,9:11);
%    end
% end
% G_r(n,1:3) = mean(Galileo_coord);
% G_r(n,5) = dataGa(i,3);
% n=n+1;
% clear Galileo_coord;
% end
%лучше так

pars(dataGa,1);
pars(dataGl,2);
pars(dataG,3);
pars(dataB,4);
 function p = pars(dataGa,nfigure)
   
%цикл берет среднее от всех значений
k = 1;
for (i = 1:length(dataGa)-20001)
    if (i == 1)
     meann(1,k) = mean(dataGa(i:1:i+20000,1));
     meann(2:4,k) = mean(dataGa(i:1:i+20000,2:4));
%      stdd(1,k) = std(dataGa(i:1:i+20000,3));
      k =k+1;
    end
if (mod(i,20001) == 0)
     meann(1,k) = mean(dataGa(i+1:1:i+20001,1));
     meann(2:4,k) = mean(dataGa(i+1:1:i+20001,2:4));
%      stdd(1,k) = std(dataGa(i+1:1:i+20001,3));
      k =k+1;
end
end
for (i = 1:length(meann))
sko(i) = 3*sqrt((meann(2,i))^2+(meann(3,i))^2);
end
 if (mod(nfigure,1) == 0)
       name ='GALILEO';
    end
     if (mod(nfigure,2) == 0)
        name ='√ЋќЌј——';
     end
     if (mod(nfigure,3) == 0)
        name ='GPS';
     end
       if (mod(nfigure,4) == 0)
        name ='BEIDOU';
    end
figure (nfigure)
plot(meann(1,:),sko);
title(name); 
xlabel('Ўирота, градусы')
ylabel('3*\sigma, м');
hold on;
grid on;
m2 = "B";
jpge = ".jpg";
saveas(nfigure,name+m2+jpge);
 end
%  function p = pars(dataGa,nfigure)
% zero =0;
% %занул€ет сингул и в обалсти не видимости
% for (i = 1:length(dataGa))
% if (dataGa(i,9)  == -10)
%     dataGa(i,9:11) =0;
%     zero = zero +1;
% end
%     if (dataGa(i,9)  == -1)
%      dataGa(i,9:11) =0;   
%     zero = zero +1;
%     end
% end   
%     
% %цикл берет среднее от всех значений
% k = 1;
% for (i = 1:length(dataGa)-20001)
%     if (i == 1)
%      meann(1,k) = mean(dataGa(i:1:i+20000,3));
%      meann(2:4,k) = mean(dataGa(i:1:i+20000,9:11));
% %      stdd(1,k) = std(dataGa(i:1:i+20000,3));
%       k =k+1;
%     end
% if (mod(i,20001) == 0)
%      meann(1,k) = mean(dataGa(i+1:1:i+20001,3));
%      meann(2:4,k) = mean(dataGa(i+1:1:i+20001,9:11));
% %      stdd(1,k) = std(dataGa(i+1:1:i+20001,3));
%       k =k+1;
% end
% end
% for (i = 1:length(meann))
% sko(i) = 3*sqrt((meann(2,i))^2+(meann(3,i))^2);
% end
%  if (mod(nfigure,1) == 0)
%        name ='GALILEO';
%     end
%      if (mod(nfigure,2) == 0)
%         name ='√ЋќЌј——';
%      end
%      if (mod(nfigure,3) == 0)
%         name ='GPS';
%      end
%        if (mod(nfigure,4) == 0)
%         name ='BEIDOU';
%     end
% figure (nfigure)
% plot(meann(1,:),sko);
% title(name); 
% xlabel('Ўирота, градусы')
% ylabel('3*\sigma, м');
% hold on;
% grid on;
% m2 = "B";
% jpge = ".jpg";
% saveas(nfigure,name+m2+jpge);
%  end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % 
%  function p = pars(dataGa,nfigure)
% zero =0;
% %занул€ет сингул и в обалсти не видимости
% for (i = 1:length(dataGa))
% if (dataGa(i,9)  == -10)
%     dataGa(i,9:11) =0;
%     zero = zero +1;
% end
%     if (dataGa(i,9)  == -1)
%      dataGa(i,9:11) =0;   
%     zero = zero +1;
%     end
% end   
%     
% %цикл берет среднее от всех значений
% k = 1;
% for (i = 1:length(dataGa)-20001)
%     if (i == 1)
%      meann(1,k) = mean(dataGa(i:1:i+20000,3));
%    %  meann(2:4,k) = mean(dataGa(i:1:i+20000,9:11));
%      sigmax(k) = mean(dataGa(i:1:i+20001,9));
%      sigmay(k) = mean(dataGa(i:1:i+20001,10));
% %      stdd(1,k) = std(dataGa(i:1:i+20000,3));
%       k =k+1;
%     end
% if (mod(i,20001) == 0)
%      meann(1,k) = mean(dataGa(i+1:1:i+20001,3));
% %      meann(2:4,k) = mean(dataGa(i+1:1:i+20001,9:11));
% %      stdd(1,k) = std(dataGa(i+1:1:i+20001,3));
%      sigmax(k) = mean(dataGa(i+1:1:i+20001,9));
%      sigmay(k) = mean(dataGa(i+1:1:i+20001,10));
% k =k+1;
% end
% end
% for (i = 1:length(meann))
% % sko(i) = 3*sqrt((meann(2,i))^2+(meann(3,i))^2);
%  sigma(i) = sqrt(sigmax(i).^2+sigmay(i).^2);
% sigma(i) = 3*sigma(i);
% end
% 
% plot(meann(1,:),sigma);
% %title(name); 
% xlabel('Ўирота, градусы')
% ylabel('3*\sigma, м');
% hold on;
% grid on;
% legend('GALILEO','√ЋќЌј——','GPS','Location','northwest' );
% m2 = "B";
% jpge = ".jpg";
% name = "all"
% saveas(gcf,name+m2+jpge);
%  end

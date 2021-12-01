clear
Datatest = "..\test.txt";
data = importdata(Datatest);
for i = 1:length(data)
    x(i) = sqrt(data(i,1)^2+data(i,2)^2+data(i,3)^2);
end
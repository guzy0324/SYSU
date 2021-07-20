%plot Score-time
t=data(:,1);
s=data(:,2);
cou=data(:,3);
[len,wid]=size(data);
realtime=1;
myrate=data(1,2);
daycount=1;
newdata=[];
for i=1:len
    if data(i,1)==realtime
    myrate=myrate+data(i,2);
    daycount=daycount+1;
    else
        newdata(realtime)=myrate/daycount;
        myrate=data(i,2);
        daycount=1;
        realtime=realtime+1;
    end
end
len2=length(newdata);
t2=1:len2;
t3=t2-t2(len2/2);
result=zeros(len2,1);
for i=1:len2
    result(i)=b_model(newdata(1:i),t3(1:i));
end
fid=figure;
set(fid,'defaultaxesfontsize',12);
plot(t2(25:10:end)',result(25:10:end)','linewidth',2)
set(gca,'xticklabel',[]);
xlabel('Time(days)');ylabel('SSR-Score')

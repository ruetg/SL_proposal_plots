%Z1=SaveStuff{end,1};
%E1=SaveStuff{end,2}-SaveStuff{end-16,2};
dx=90;
dy=dx;
if 1
    [mm,nn]=size(Z1);
    [LON,LAT]=meshgrid(1:nn,1:mm);
    dt=1000;
    m=.45;
    k=1.2e-6;
    BC=find(Z1<0);
    acc=ones(mm,nn);%length(FD.ix(i)));
    Z1=Z1;
    
    Z1 = lands(dx,dy,nn,mm,0,Z1(:),zeros(mm*nn,1),BC(:),zeros(mm*nn,1),zeros(mm*nn,1));
    Z1=reshape(Z1,mm,nn);
    
    
    [~,I,R] = erosion(dx,dy,nn,mm,dt,1,zeros(mm*nn,1),0,Z1(:),BC(:),1,1,.5);
    FD.I=I;
    FD.R=R;
    des = ismember(I,BC);
    I = I(~des);
    
    FD.ix = fliplr(I);
    
    FD.ixc = R(FD.ix);
    Z12=Z1;
    for i=1:length(FD.ix)
        acc(FD.ixc(i))=acc(FD.ixc(i))+acc(FD.ix(i));
    end
end
if 1
    plotstrm;
    [x,y]=ginput(1);
end
%x=(x-min(LON(:))).*3600/30;
%y=(y-min(LAT(:))).*3600/30;


id=(sub2ind([mm,nn],floor(y),floor(x)));

r=find(FD.ix==id);

i1=FD.ix(r);
ilist=[];
r2=1;
while ~ismember(FD.ixc(r),BC)
    if FD.ix(r)==i1
        ilist(r2)=FD.ix(r);
        r2=r2+1;
        i1=FD.ixc(r);
    end
    r=r+1;
    if r>length(FD.ixc)
        break
    end
    
end
hold on;
[y,x]=ind2sub([mm,nn],ilist);
%plot(x,y,'r');

dist=((x(2:end)-x(1:end-1)).^2+(y(2:end)-y(1:end-1)).^2).^.5;
s=(Z1(ilist(1:end-1))-Z1(ilist(2:end)))./(dist*dx);
figure;
plot(cumsum(dist),Z1(ilist(1:end-1)));
hold on
%plot(dist,Z1(ilist(1:end-1)));%+E1(ilist))


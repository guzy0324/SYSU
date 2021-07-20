function [] = change2(A)
    [len1,wid]=size(A);	%把变量名设为A，读入为字符串数�?
    kindof=[""];
    for i=1:len1
        cutlen=length(kindof);
        if ~ismember(A{i,4},kindof)
            if kindof(1)==""
                kindof(1)=A(i,4);
            else
                kindof(cutlen+1)=A(i,4);
            end
        end
    end    
    len2=length(kindof);
    all{len2}=[""];
    for i=1:len1
        temp=A(i,4);
        k=strfind(kindof,temp);
        for j=1:length(k)
            aaa=isempty(k{j});                                    
            if aaa==0
                index=j;                                        
                break
            end
        end
        len3=length(all{index});
        if isempty(all{index})
            all{index}=A(i,:);
        else
            if all{index}==[""]
                all{index}=A(i,:);
            else
            all{index}=[all{index};A(i,:)];
            end
        end
    end
end
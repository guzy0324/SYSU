use school
go
create procedure p
    @id char(10),
    @name char(10),
    @email char(10),
    @salary int,
    @return varchar(100) out
as
begin tran
    if exists(select tid from teachers where tid = @id)
        begin
            select @return = '�����Ѵ���'
            goto err
        end
    insert into teachers values(@id, @name, @email, @salary)
    if @@error != 0
        begin
            select @return = '��������ʧ��'
            goto err
        end
    select @return = '�������ݳɹ�'
    print @return
    commit tran
    goto succ
err:
    print @return
    commit tran
succ:
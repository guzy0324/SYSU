use school
go
begin tran t1
    update students
    set sname = 'kk'
    where sid = '800002933'
    begin tran t2
        insert into teachers
        values ('200003125', 'gk', 'gk', 0)
        if @@error != 0
            begin
                rollback tran t1
                print 'hahahahaha'
                return
            end
    commit tran t2
commit tran t1

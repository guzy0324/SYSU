use school
go
begin tran T1
    update students set grade=0 where sid='889358356'
    waitfor delay '00:00:10'
    select * from students where sid='889358356'
    rollback tran
    select * from students where sid='889358356'

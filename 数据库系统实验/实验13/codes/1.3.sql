use school
go
set transaction isolation level read uncommitted
select * from students where sid='889358356'
if @@rowcount<>0
    begin
        waitfor delay '00:00:10'
        select * from students where sid='889358356'
end

use school
go
create trigger T4 on worker
for insert
as
if (select sage from inserted) <= (select max(sage) from worker)
begin
print 'Transaction fail'
rollback transaction
end
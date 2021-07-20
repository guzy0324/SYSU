use school
go
create trigger T5 on worker
for update
as
if (select sage from inserted) <= (select sage from deleted)
begin
print 'Transaction fail'
rollback transaction
end

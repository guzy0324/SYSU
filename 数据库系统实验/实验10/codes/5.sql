use school
go
create rule r2 as @value between 1 and 100
go
exec sp_bindrule r2, 'worker.[sage]';
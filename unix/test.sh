LS=`ls`
select fname in $LS;
do
    echo you picked $fname \($REPLY\)
    break;
done
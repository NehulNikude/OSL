#!/bin/sh

display()
{
	echo -n "\nEnter Name Of Database : "
	read dbname
	
	res=`ls | grep $dbname | wc -c`
	
	if [ $res -gt 0 ]
	then
		cat $dbname
	else
		echo "\nFile Doesn't Exist!"
	fi
}

insert()
{
	echo -n "\nEnter Name Of Database : "
	read dbname
	
	res=`ls | grep "$dbname" | wc -c`
	
	if [ $res -gt 0 ]
	then
		echo -n "\nEnter Mobile Number : "
		read mb
		len=`echo -n "$mb" | wc -c`
		if [ $len -ne 10 ]
		then
			echo "\nEnter Valid Mobile Number"
		else
			check=`cat $dbname | grep $mb | wc -c`
			if [ "$check" -gt 0 ]
			then
				echo "\nMobile Number Already Exists!"
			else
				echo -n "\nEnter Name Of Student : "
				read name
				echo -n "\nEnter Department : "
				read dept
				echo -n "\nEnter Achievement : "
				read ach
				
				record=`echo "$name\t$dept\t$ach\t$mb"`
				echo $record >> $dbname
				echo "\nRecord Inserted Successfully"
			fi
		fi
	else
		echo "\nFile Doesn't Exist!"
	fi
}

modify()
{
	echo -n "\nEnter Name Of Database : "
	read dbname
	
	res=`ls | grep "$dbname" | wc -c`
	
	if [ $res -gt 0 ]
	then
		echo -n "\nEnter Mobile Number Of The Record To Be Modified : "
		read mb
		len=`echo -n "$mb" | wc -c`
		if [ $len -ne 10 ]
		then
			echo "\nEnter Valid Mobile Number"
		else
			check=`cat $dbname | grep $mb | wc -c`
			if [ "$check" -gt 0 ]
			then
				echo "\nEnter New Data"
				echo -n "\nEnter Name Of Student : "
				read name
				echo -n "\nEnter Department : "
				read dept
				echo -n "\nEnter Achievement : "
				read ach
				
				new=`echo $name $dept $ach $mb`
				old=`cat $dbname | grep $mb`
				sed -i s/"$old"/"$new"/g $dbname
				echo "\nRecord Modified Successfully"
			else
				echo "\nRecord Doesn't Exist"
			fi
		fi
	else
		echo "\nFile Doesn't Exist!"
	fi
}

delete()
{
	echo -n "\nEnter Name Of Database : "
	read dbname
	
	res=`ls | grep "$dbname" | wc -c`
	
	if [ $res -gt 0 ]
	then
		echo -n "\nEnter Mobile Number Of The Record To Be Deleted : "
		read mb
		len=`echo -n "$mb" | wc -c`
		if [ $len -ne 10 ]
		then
			echo "\nEnter Valid Mobile Number"
		else
			check=`cat $dbname | grep $mb | wc -c`
			if [ "$check" -gt 0 ]
			then
				old=`cat $dbname | grep $mb`
				sed -i s/"$old"//g $dbname
				sed -i '/^$/d' $dbname
				echo "\nRecord Deleted Successfully"
			else
				echo "\nRecord Doesn't Exist"
			fi
		fi
	else
		echo "\nFile Doesn't Exist!"
	fi
}

create()
{
	echo -n "\nEnter Name Of Database : "
	read dbname
	
	res=`ls | grep "$dbname" | wc -c`
	
	if [ $res -gt 0 ]
	then
		echo "\nError! File Already Exists"
	else
		touch $dbname
		echo "\nFile Created Successfully!"
	fi
}



while [ true ]
do
	echo "\n**********MENU**********"
	echo "1. Create Database"
	echo "2. Insert Data"
	echo "3. Display Data"
	echo "4. Modify Data"
	echo "5. Delete Data"
	echo "6. Exit\n"
	
	echo -n "Enter Your Choice : "
	read choice
	
	case $choice in
		1) create ;;
		
		2) insert ;;
		
		3) display ;;
		
		4) modify ;;
		
		5) delete ;;
		
		6) echo " "
			 exit ;;
		
		*) echo "Enter Valid Choice!\n" ;;
	esac
done

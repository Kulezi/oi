oi=(
    'i ii iii iv v vi vii viii ix x'
    'xi xii xiii xiv xv xvi xvii xviii xix xx'
    'xxi xxii xxiii xxiv xxv xxvi xxvii xxviii xxix xxx'
    'xxxi'
)

# etap_tasks etap dzien
etap_tasks() {
    if [ $1 == 'etap1' ]; then
        echo 5
    elif [ $1 == 'etap2' ]; then
        if [ $2 == 'probne' ]; then
            echo 1
        else
            echo 2
        fi
    elif [ $1 == 'etap3' ]; then
        if [ $2 == 'probne' ]; then
            echo 2
        else
            echo 3
        fi
    fi
}

for oi_dir in ${oi[*]}; do
    echo -ne $oi_dir
    if [ -d "$oi_dir" ]; then
        # 1 Etap nie dzieli się na dni.
        rem_tasks=$(etap_tasks etap1 brak)
        for task_dir in $oi_dir/etap1/*; do
            if [ -d $task_dir ]; then
                task_name=$(basename $task_dir)
                if [ -f $task_dir/${task_name}.cpp ]; then
                    echo -ne ,$task_name
                    ((rem_tasks--))
                fi
            fi
        done

        for i in $(seq 1 $rem_tasks); do
            echo -ne ,
        done

        for etap in etap2 etap3; do
            for dzien in probne dzien1 dzien2; do
                rem_tasks=$(etap_tasks $etap $dzien)
                if [ -d "$oi_dir/$etap" ]; then
                    for task_dir in $oi_dir/$etap/$dzien/*; do
                        if [ -d $task_dir ]; then
                            task_name=$(basename $task_dir)
                            if [ -f $task_dir/${task_name}.cpp ]; then
                                echo -ne ,$task_name
                                ((rem_tasks--))
                            fi
                        fi
                    done
                fi
                for i in $(seq 1 $rem_tasks); do
                    echo -ne ,
                done
            done
        done
    fi

    echo
done

/**
 * Created by sun on 2017/9/18.
 */
function menuClick(index) {
    switch (index) {
        case 1:
        {
            Show_Information();
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
    }
}


function Show_Information()
{
    MyGetJSONWithArg("loading","/cgi-bin/getDevInfo?","", function (info)
    {
        $("#u_type").innerHTML = info.u_type;
        $("#u_hardware_version").innerHTML = info.u_hardware_version;
        $("#u_serial_no").innerHTML = info.u_serial_no;
        $("#u_kernel_version").innerHTML = info.u_kernel_version;
        $("#u_app_version").innerHTML = info.u_app_version;
        $("#u_activate_no").innerHTML = info.u_activate_no;
        $("#u_activate").innerHTML = info.u_activate;
        $("#u_cpu").innerHTML = info.u_cpu;
        $("#u_memory").innerHTML = info.u_memory;
        $("#u_flash").innerHTML = info.u_flash;
        $("#u_ethernet").innerHTML = info.u_ethernet;
        $("#u_clock").innerHTML = info.u_clock;
        $("#u_compile_date").innerHTML = info.u_compile_date;
    });
}

function SystemBackup(type)
{
    MyGetJSONWithArg("loading","/cgi-bin/systemBackup?","u_type="+type, function (info)
    {
        if(info==0)
        {
            alert( "备份成功" );
        }else
        {
            alert("备份失败,请重试");
        }

    });
}

function firmwareBack(info)
{
    if(info==0)
    {
        alert( "更新成功" );
    }else
    {
        alert("更新失败,请重试");
    }
}

function Restore()
{
    var u_password = $("#u_password").val();
    MyGetJSONWithArg("loading","/cgi-bin/systemRestore?","u_password="+u_password, function (info)
    {
        if(info==0)
        {
            alert( "恢复设置成功" );
        }else
        {
            alert("恢复设置失败,请重试");
        }
    });
}

function Restart()
{
    resetdev();
}
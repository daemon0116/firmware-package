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
    MyGetJSONWithArg("loading","/action/getDevInfo?","", function (info)
    {
		document.getElementById("u_type").innerHTML = info.u_type;
        document.getElementById("u_hardware_version").innerHTML = info.u_hardware_version;
        document.getElementById("u_serial_no").innerHTML = info.u_serial_no;
        document.getElementById("u_kernel_version").innerHTML = info.u_kernel_version;
        document.getElementById("u_app_version").innerHTML = info.u_app_version;
        document.getElementById("u_activate_no").innerHTML = info.u_activate_no;
        document.getElementById("u_activate").innerHTML = info.u_activate;
        document.getElementById("u_cpu").innerHTML = info.u_cpu;
        document.getElementById("u_memory").innerHTML = info.u_memory;
        document.getElementById("u_flash").innerHTML = info.u_flash;
        document.getElementById("u_ethernet").innerHTML = info.u_ethernet;
        document.getElementById("u_clock").innerHTML = info.u_clock;
        document.getElementById("u_compile_date").innerHTML = info.u_compile_date;
    });
}

function SystemBackup(type)
{
    MyGetJSONWithArg("loading","/action/systemBackup?","u_type="+type, function (info)
    {
        if(info.ret==0)
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
    MyGetJSONWithArg("loading","/action/systemRestore?","u_password="+u_password, function (info)
    {
        if(info.ret==0)
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
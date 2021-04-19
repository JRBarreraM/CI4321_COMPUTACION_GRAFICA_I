using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class NotManager : MonoBehaviour
{
    public static NotManager current;

    private void Awake ()
    {
        current = this;
    }

    public event Action makeItBunDem;
    public void MakeItBunDem()
    {
        if (makeItBunDem != null) makeItBunDem();
    }
    public event Action leaveTheBunDem;
    public void LeaveTheBunDem()
    {
        if (makeItBunDem != null) leaveTheBunDem();
    }


    void Update()
    {
        if (Input.GetKeyDown(KeyCode.M)){
            current.MakeItBunDem();
        }
        if (Input.GetKeyDown(KeyCode.N)){
            current.LeaveTheBunDem();
        }
    }
}

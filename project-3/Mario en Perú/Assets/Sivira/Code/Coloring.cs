using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Coloring : MonoBehaviour
{
    public Renderer rend;

    private enum Colors {r, g, b, n};
    private Colors color = Colors.n;

    void Start() {
        rend = GetComponent<Renderer> ();
        StartCoroutine("UpdateColor");
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public static RGB HSVToRGB(HSV hsv)
    {
        double r = 0, g = 0, b = 0;

        if (hsv.S == 0)
        {
            r = hsv.V;
            g = hsv.V;
            b = hsv.V;
        }
        else
        {
            int i;
            double f, p, q, t;

            if (hsv.H == 360)
                hsv.H = 0;
            else
                hsv.H = hsv.H / 60;

            i = (int)Math.Truncate(hsv.H);
            f = hsv.H - i;

            p = hsv.V * (1.0 - hsv.S);
            q = hsv.V * (1.0 - (hsv.S * f));
            t = hsv.V * (1.0 - (hsv.S * (1.0 - f)));

            switch (i)
            {
                case 0:
                    r = hsv.V;
                    g = t;
                    b = p;
                    break;

                case 1:
                    r = q;
                    g = hsv.V;
                    b = p;
                    break;

                case 2:
                    r = p;
                    g = hsv.V;
                    b = t;
                    break;

                case 3:
                    r = p;
                    g = q;
                    b = hsv.V;
                    break;

                case 4:
                    r = t;
                    g = p;
                    b = hsv.V;
                    break;

                default:
                    r = hsv.V;
                    g = p;
                    b = q;
                    break;
            }

        }

        return new RGB((byte)(r * 255), (byte)(g * 255), (byte)(b * 255));
    }

    IEnumerator UpdateColor() 
    {
        for(;;) 
        {
            Debug.Log(color);

            switch (color)
            {
                case Colors.r:
                    rend.material.SetFloat ("_R", 1.0f);
                    rend.material.SetFloat ("_G", 0.0f);
                    rend.material.SetFloat ("_B", 0.0f);
                    color = Colors.g;
                    break;
                case Colors.g:
                    rend.material.SetFloat ("_R", 0.0f);
                    rend.material.SetFloat ("_G", 1.0f);
                    rend.material.SetFloat ("_B", 0.0f);
                    color = Colors.b;
                    break;
                case Colors.b:
                    rend.material.SetFloat ("_R", 0.0f);
                    rend.material.SetFloat ("_G", 0.0f);
                    rend.material.SetFloat ("_B", 1.0f);
                    color = Colors.n;
                    break;
                case Colors.n:
                    rend.material.SetFloat ("_R", 0.0f);
                    rend.material.SetFloat ("_G", 0.0f);
                    rend.material.SetFloat ("_B", 0.0f);
                    color = Colors.r;
                    break;
            }

            yield return new WaitForSeconds(0.1f);
        }
    }
}

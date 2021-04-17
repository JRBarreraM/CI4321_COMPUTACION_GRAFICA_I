using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

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
        for (int i = 0; i <= 360; i++)
        {
            Debug.Log("R: " + HSVToRGB(i)[0]);
            Debug.Log("G: " + HSVToRGB(i)[1]);
            Debug.Log("B: " + HSVToRGB(i)[2]);
            Debug.Log("--------------------");
        }
    }

    double[] HSVToRGB(int h)
    {
        double[] rgb = {0.0, 0.0, 0.0};
        double r = 0, g = 0, b = 0;
        int i;
        double f, p, q, t;

        if (h == 360)
            h = 0;
        else
            h = h / 60;

        i = (int)Math.Truncate(h * 1.0f);
        f = h - i;

        p = 100 * (1.0 - 100);
        q = 100 * (1.0 - (100 * f));
        t = 100 * (1.0 - (100 * (1.0 - f)));

        switch (i)
        {
            case 0:
                r = 100;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = 100;
                b = p;
                break;

            case 2:
                r = p;
                g = 100;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = 100;
                break;

            case 4:
                r = t;
                g = p;
                b = 100;
                break;

            default:
                r = 100;
                g = p;
                b = q;
                break;
        }

        rgb[0] = r * 255;
        rgb[1] = g * 255;
        rgb[2] = b * 255;

        return rgb;
    }

    IEnumerator UpdateColor() 
    {
        for(;;) 
        {
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

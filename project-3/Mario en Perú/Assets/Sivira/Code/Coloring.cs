using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Coloring : MonoBehaviour
{
    public Transform target;

    public struct RGB
    {
        private byte _r;
        private byte _g;
        private byte _b;

        public RGB(byte r, byte g, byte b)
        {
            this._r = r;
            this._g = g;
            this._b = b;
        }

        public byte R
        {
            get { return this._r; }
            set { this._r = value; }
        }

        public byte G
        {
            get { return this._g; }
            set { this._g = value; }
        }

        public byte B
        {
            get { return this._b; }
            set { this._b = value; }
        }

        public bool Equals(RGB rgb)
        {
            return (this.R == rgb.R) && (this.G == rgb.G) && (this.B == rgb.B);
        }
    }

    public struct HSV
    {
        private double _h;
        private double _s;
        private double _v;

        public HSV(double h, double s, double v)
        {
            this._h = h;
            this._s = s;
            this._v = v;
        }

        public double H
        {
            get { return this._h; }
            set { this._h = value; }
        }

        public double S
        {
            get { return this._s; }
            set { this._s = value; }
        }

        public double V
        {
            get { return this._v; }
            set { this._v = value; }
        }

        public bool Equals(HSV hsv)
        {
            return (this.H == hsv.H) && (this.S == hsv.S) && (this.V == hsv.V);
        }
    }

    private Renderer rend;
    private double h;

    void Awake()
    {
        rend = GetComponent<Renderer> ();
    }

    private void ClearColor() {
        rend.material.SetFloat ("_R", 1.0f);
        rend.material.SetFloat ("_G", 1.0f);
        rend.material.SetFloat ("_B", 1.0f);
        rend.material.SetFloat ("_A", 5.0f);
        rend.material.SetFloat ("_AA", 0.0f);
    }

    private void Start()
    {
        NotManager.current.makeItBunDem += MakeItBunDem;
        NotManager.current.leaveTheBunDem += LeaveTheBunDem;

        ClearColor();
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

            i = (int)Mathf.Round((float)hsv.H);
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

    private void MakeItBunDem()
    {
        rend.material.SetFloat ("_A", 0.05f);
        StartCoroutine("UpdateColor");
    }

    private void LeaveTheBunDem()
    {
        ClearColor();
        StopCoroutine("UpdateColor");
    }

    IEnumerator UpdateColor() 
    {
        int frequency1 = 1;
        int frequency2 = 2;
        int frequency3 = 3;
        int phase1 = 0;
        int phase2 = 2;
        int phase3 = 4;
        int center = 128;
        int width = 128;
        int len = 50;

        for(;;) 
        {
            float h1  = Random.Range(0, len);
            float h2  = Random.Range(0, len);
            float h3  = Random.Range(0, len);

            double red = Mathf.Sin(frequency1*h1 + phase1) * width + center;
            double grn = Mathf.Sin(frequency2*h2 + phase2) * width + center;
            double blu = Mathf.Sin(frequency3*h3 + phase3) * width + center;

            rend.material.SetFloat ("_R", (float)red);
            rend.material.SetFloat ("_G", (float)grn);
            rend.material.SetFloat ("_B", (float)blu);

            yield return new WaitForSeconds(0.1f);
        }
    }

    /*
        Fuente de HSVTORGB
        https://www.programmingalgorithms.com/algorithm/hsv-to-rgb/
    */
}

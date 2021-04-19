using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleDestruction : MonoBehaviour
{
    void DestroyMe()
    {
        GameObject.Destroy(gameObject);
    }
    // Start is called before the first frame update
    void Start()
    {
        Invoke("DestroyMe",2.0f);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

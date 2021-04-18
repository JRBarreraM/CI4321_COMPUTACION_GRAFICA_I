using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MushroomBox : MonoBehaviour
{
    public AudioManager1 audMan;
    public GameObject Mushroom;
    private bool opened = false;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if (!opened && (((this.transform.position.y - col.collider.transform.position.y) > 0) && (Mathf.Abs(col.collider.transform.position.x - this.transform.position.x) < 1)))
        {
                audMan.Play("Mushroom Box");
                // Cambia Sprite
                Instantiate(Mushroom, gameObject.transform.position, Quaternion.identity);
                opened = true;
        }
    }
}

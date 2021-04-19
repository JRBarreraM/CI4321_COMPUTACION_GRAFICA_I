using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoxBreaker : MonoBehaviour
{
    public AudioManager1 audMan;
    // Start is called before the first frame update
    void Awake()
	{
		audMan = GameObject.Find("GameManager").GetComponent<AudioManager1>();
	}
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if (((this.transform.position.y - col.collider.transform.position.y) > 0) && (Mathf.Abs(col.collider.transform.position.x - this.transform.position.x) < 1))
        {
                audMan.Play("Block Destroy");
                // animation destroy
                print("BREAK");
        }
    }
}

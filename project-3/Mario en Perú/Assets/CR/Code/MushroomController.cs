using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MushroomController : MonoBehaviour
{

    public float moveSpeed = 200f;
    private float direction = 0;
    public AudioManager1 audMan;
    private bool outside = false;
    private float posY;
    
    void Awake()
	{
		audMan = GameObject.Find("GameManager").GetComponent<AudioManager1>();
	}
    // Start is called before the first frame update
    void Start()
    {
        GetComponent<Rigidbody2D>().velocity = new Vector2(0,100*Time.deltaTime);
        posY = gameObject.transform.position.y;
    }

    // Update is called once per frame
    void Update()
    {
        if(!outside && (gameObject.transform.position.y >= posY + 1))
        {
            GetComponent<Rigidbody2D>().velocity = new Vector2(0,0);
            gameObject.GetComponent<Rigidbody2D>().gravityScale = 1;
            direction = 1;
            gameObject.GetComponent<BoxCollider2D>().enabled = true;
            outside = true;
        }
    }
    
    void FixedUpdate()
    {
        if(outside)
        {
            GetComponent<Rigidbody2D>().velocity = new Vector2(direction * moveSpeed * Time.deltaTime,GetComponent<Rigidbody2D>().velocity.y);
        }
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if(col.gameObject.CompareTag("Wall") || col.gameObject.CompareTag("Enemy"))
        {
            direction *= -1;
        }
    }
}

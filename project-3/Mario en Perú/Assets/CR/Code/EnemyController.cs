using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{

    public float moveSpeed = 50f;
    private float direction = -1;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    
    void FixedUpdate()
    {
        if(GetComponent<Rigidbody2D>().velocity.x < 0) {
			this.transform.localScale = new Vector3(-1,1,1);
		}

		if(GetComponent<Rigidbody2D>().velocity.x > 0) {
			this.transform.localScale = new Vector3(1,1,1);
		}
        GetComponent<Rigidbody2D>().velocity = new Vector2(direction * moveSpeed * Time.deltaTime,GetComponent<Rigidbody2D>().velocity.y);

    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if(col.gameObject.CompareTag("Wall"))
        {
            direction *= -1;
        }

        if(col.gameObject.name.Equals("Player"))
        {
            if (((this.transform.position.y - col.collider.transform.position.y) < 0) && (Mathf.Abs(col.collider.transform.position.x - this.transform.position.x) < 1)) 
            {
                print("DEAD");
            }
        }
    }
}

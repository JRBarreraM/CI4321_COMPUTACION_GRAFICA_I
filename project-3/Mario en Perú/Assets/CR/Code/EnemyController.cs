using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{

    public float moveSpeed = 150f;
    private float direction = -1;
    public AudioManager1 audMan;
    public Animator animator;
    private bool dead = false;
    
    void Awake()
	{
		audMan = GameObject.Find("GameManager").GetComponent<AudioManager1>();
	}
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
        if(!dead)
        {
            if(GetComponent<Rigidbody2D>().velocity.x < 0) {
                this.transform.localScale = new Vector3(-1,1,1);
            }

            if(GetComponent<Rigidbody2D>().velocity.x > 0) {
                this.transform.localScale = new Vector3(1,1,1);
            }
            GetComponent<Rigidbody2D>().velocity = new Vector2(direction * moveSpeed * Time.deltaTime,GetComponent<Rigidbody2D>().velocity.y);
        }
    }

    void DestroyMe()
    {
        GameObject.Destroy(gameObject);
    }
    void OnCollisionEnter2D(Collision2D col)
    {
        if(col.gameObject.CompareTag("Wall") || col.gameObject.CompareTag("Enemy") || col.gameObject.CompareTag("Mushroom"))
        {
            direction *= -1;
        }

        if(col.gameObject.name.Equals("Player"))
        {
            if(col.gameObject.GetComponent<Mario1Controller2DScript>().invincible)
            {
                audMan.Play("Enemy Death");
                animator.SetBool("Dead", true);
                gameObject.GetComponent<Rigidbody2D>().gravityScale = 0;
                gameObject.GetComponent<BoxCollider2D>().enabled = false;
                gameObject.GetComponent<Rigidbody2D>().velocity = new Vector2(0,0);
                Invoke("DestroyMe", 1.06f);
                dead = true;
                print("DEAD");
            }
            else if (((this.transform.position.y - col.collider.transform.position.y) < 0) && (Mathf.Abs(col.collider.transform.position.x - this.transform.position.x) < 1)) 
            {
                audMan.Play("Enemy Death");
                animator.SetBool("Dead", true);
                gameObject.GetComponent<Rigidbody2D>().gravityScale = 0;
                gameObject.GetComponent<BoxCollider2D>().enabled = false;
                gameObject.GetComponent<Rigidbody2D>().velocity = new Vector2(0,0);
                Invoke("DestroyMe", 1.06f);
                dead = true;
                print("DEAD");
            }
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public int Hearts = 3;
    public AudioManager1 audMan;
    public bool dead = false;
    void RestartScene()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex, LoadSceneMode.Single);
    }
    void ChangeScene()
    {
        SceneManager.LoadScene("Game Over", LoadSceneMode.Single);
    }
    void StartScene()
    {
        SceneManager.LoadScene("Movement", LoadSceneMode.Single);
    }
    void Awake()
    {

    }
    // Start is called before the first frame update
    void Start()
    {
        //audMan.Play("Main Theme");
    }

    // Update is called once per frame
    void Update()
    {
        if(dead)
        {
            Hearts -= 1;
            if(Hearts < 0)
            {
                Invoke("ChangeScene", 4.0f);
            }
            else {
                Invoke("StartScene", 4.0f);
            }
            dead = false;
        }
    }
}

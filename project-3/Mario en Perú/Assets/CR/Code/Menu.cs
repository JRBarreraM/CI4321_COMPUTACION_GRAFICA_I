using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{
    void Start()
    {
        GameObject.Find("GameManager").GetComponent<AudioManager1>().Play("Game Over");
    }
    public void RestartGame()
    {
        GameObject.Find("GameManager").GetComponent<AudioManager1>().Stop("Game Over");
        GameObject.Find("GameManager").GetComponent<AudioManager1>().Play("Main Theme");
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex - 1);
    }
    public void QuitGame()
    {
        Application.Quit();
    }

}

package com.item;

public class ItemBuilder {

    // Builder pt clasa Item
    private ItemType itemType;
    private int hp = 0;
    private int attack = 0;
    private int defense = 0;
    private int specialAttack = 0;
    private int specialDefense = 0;

    public void setItemType(ItemType itemType) {
        this.itemType = itemType;
    }

    public void setHp(int hp) {
        this.hp = hp;
    }

    public void setAttack(int attack) {
        this.attack = attack;
    }

    public void setDefense(int defense) {
        this.defense = defense;
    }

    public void setSpecialAttack(int specialAttack) {
        this.specialAttack = specialAttack;
    }

    public void setSpecialDefense(int specialDefense) {
        this.specialDefense = specialDefense;
    }

    public Item getResult(){
        return new Item(itemType,hp,attack,defense,specialAttack,specialDefense);
    }
}
